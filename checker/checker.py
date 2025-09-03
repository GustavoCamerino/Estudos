#!/usr/bin/env python3
"""
CHDEVSEC - Pentest Recon | Email & Password Breach Checker v2.1
By Caio Henrique | @CHDEVSEC

# Keywords SEO: Email Breach Checker | Password Breach Checker | Vazamento de Emails e Senhas | Breached.me LeakCheck HaveIBeenPwned | Segurança da Informação
"""

import requests, time, csv, os, re, argparse, hashlib, socket, logging
from tqdm import tqdm
from colorama import Fore, init
init(autoreset=True)

def print_banner():
    print(Fore.CYAN + r"""
╔══════════════════════════════════════════════════════════╗            
║ /$$$$$$$$                         /$$ /$$                ║
║| $$_____/                        |__/| $$                ║
║| $$       /$$$$$$/$$$$   /$$$$$$  /$$| $$  /$$$$$$$      ║
║| $$$$$   | $$_  $$_  $$ |____  $$| $$| $$ /$$_____/      ║
║| $$__/   | $$ \ $$ \ $$  /$$$$$$$| $$| $$|  $$$$$$       ║
║| $$      | $$ | $$ | $$ /$$__  $$| $$| $$ \____  $$      ║
║| $$$$$$$$| $$ | $$ | $$|  $$$$$$$| $$| $$ /$$$$$$$/      ║
║|________/|__/ |__/ |__/ \_______/|__/|__/|_______/       ║   
╔══════════════════════════════════════════════════════════╗                 
║ CHDEVSEC - Email & Password Breach Checker v2.1          ║
╚══════════════════════════════════════════════════════════╝          
""")

def check_internet():
    try:
        socket.create_connection(("8.8.8.8", 53), timeout=3)
        return True
    except Exception:
        return False

def setup_logger(log_file):
    logging.basicConfig(filename=log_file, level=logging.INFO,
                        format='%(asctime)s - %(levelname)s - %(message)s')

def is_valid_email(email):
    return re.match(r'^[\w\.-]+@[\w\.-]+\.[a-zA-Z]{2,}$', email)

def check_breachedme(email):
    try:
        r = requests.get(f"https://breached.me/api/v1/lookup?email={email}", timeout=10)
        if r.status_code == 200:
            j = r.json()
            return "Vazado" if j.get("success") and j.get("result") else "Seguro"
        elif r.status_code == 404:
            return "Seguro"
        else:
            return f"Erro HTTP {r.status_code}"
    except requests.exceptions.RequestException as e:
        return f"Erro Conn: {e}"

def check_leakcheck(email):
    try:
        url = f"https://leakcheck.io/api/public?check={email}"
        r = requests.get(url, timeout=10)
        if r.status_code == 200:
            j = r.json()
            if j.get("found", 0) > 0:
                fontes = [f"{src['name']} ({src['date']})" for src in j.get("sources", [])]
                campos = ', '.join(j.get("fields", []))
                return "Vazado", campos, '; '.join(fontes)
            else:
                return "Seguro", "", ""
        else:
            return f"Erro HTTP {r.status_code}", "", ""
    except requests.exceptions.RequestException as e:
        return f"Erro Conn: {e}", "", ""

def check_password_hibp(password):
    sha1 = hashlib.sha1(password.encode('utf-8')).hexdigest().upper()
    prefix = sha1[:5]
    suffix = sha1[5:]
    url = f"https://api.pwnedpasswords.com/range/{prefix}"
    try:
        r = requests.get(url, timeout=10)
        if r.status_code == 200:
            hashes = (line.split(':') for line in r.text.splitlines())
            for h, count in hashes:
                if h == suffix:
                    return int(count)
            return 0
        else:
            return -1
    except requests.exceptions.RequestException:
        return -1

def process_emails(emails, output, password=None, sleep_time=1.5, silent=False, log_file=None):
    rows = []
    vazados_email = 0
    vazados_pass = 0

    for email in tqdm(emails, desc="Verificando e-mails", unit="email"):
        if not is_valid_email(email):
            msg = f"[Inválido] - {email}"
            if not silent: print(Fore.YELLOW + msg)
            if log_file: logging.warning(msg)
            rows.append([email, "Inválido", "", "", "", ""])
            continue

        bm_status = check_breachedme(email)
        lc_status, lc_fields, lc_sources = check_leakcheck(email)
        final_email_status = "Vazado" if "Vazado" in (bm_status, lc_status) else "Seguro"

        if final_email_status == "Vazado":
            vazados_email += 1

        if password:
            pass_count = check_password_hibp(password)
            if pass_count > 0:
                vazados_pass += 1
                pass_status = f"Vazada {pass_count} vezes"
            elif pass_count == 0:
                pass_status = "Não vazada"
            else:
                pass_status = "Erro na checagem"
        else:
            pass_status = "N/A"

        status_final = "Vazado" if final_email_status == "Vazado" or (password and pass_count > 0) else "Seguro"

        msg = f"[{status_final}] - {email} | Senha: {pass_status}"
        color = Fore.RED if status_final == "Vazado" else Fore.GREEN
        if not silent: print(color + msg)
        if log_file: logging.info(msg)

        rows.append([email, bm_status, lc_status, lc_fields, lc_sources, pass_status, status_final])
        time.sleep(sleep_time)

    header = ["Email", "Breached.me", "LeakCheck Status", "Campos Vazados", "Fontes Vazadas", "Status Senha", "Status Final"]
    with open(output, "w", newline='') as f:
        csv.writer(f).writerows([header] + rows)

    print(Fore.CYAN + f"\n[✔] Total e-mails processados: {len(emails)}")
    print(Fore.RED + f"[!] E-mails Vazados: {vazados_email} ({(vazados_email/len(emails))*100:.2f}%)")
    if password:
        print(Fore.RED + f"[!] Senhas Vazadas: {vazados_pass}")
    print(Fore.GREEN + f"[+] Resultado salvo em: {output}")

def check_only_password(password):
    print(Fore.YELLOW + "\n[+] Checando senha com HaveIBeenPwned (HIBP)...")
    count = check_password_hibp(password)
    if count > 0:
        print(Fore.RED + f"[!] Sua senha foi vazada {count} vezes!")
    elif count == 0:
        print(Fore.GREEN + "[✔] Sua senha NÃO foi encontrada em vazamentos conhecidos.")
    else:
        print(Fore.RED + "[!] Erro ao consultar a API do HIBP.")

def main():
    print_banner()

    if not check_internet():
        print(Fore.RED + "[!] Sem conexão com a internet. Verifique e tente novamente.")
        return

    parser = argparse.ArgumentParser(description="Checker de E-mails e Senhas Vazadas - CHDEVSEC")
    parser.add_argument("--file", help="Arquivo .txt com lista de e-mails (um por linha)")
    parser.add_argument("--email", help="Verificar um único e-mail")
    parser.add_argument("--password", help="Verificar se uma senha foi vazada")
    parser.add_argument("--output", help="Nome do arquivo CSV de saída", default="resultado_emails.csv")
    parser.add_argument("--sleep", type=float, help="Tempo de espera entre requisições (em segundos)", default=1.5)
    parser.add_argument("--silent", action="store_true", help="Modo silencioso (sem prints)")
    parser.add_argument("--log", help="Salvar logs em arquivo .log")
    args = parser.parse_args()

    if args.log:
        setup_logger(args.log)

    # Se for apenas --password sem e-mails
    if args.password and not args.email and not args.file:
        check_only_password(args.password)
        return

    # Se for e-mail único ou arquivo de e-mails
    if args.email:
        emails = [args.email.strip()]
    elif args.file:
        if not os.path.isfile(args.file):
            print(Fore.RED + f"[!] Arquivo '{args.file}' não encontrado.")
            return
        with open(args.file, "r") as f:
            emails = [line.strip() for line in f if line.strip()]
    else:
        print(Fore.YELLOW + "\n[!] Use --email, --file ou --password para iniciar")
        parser.print_help()
        return

    process_emails(emails, args.output, password=args.password, sleep_time=args.sleep, silent=args.silent, log_file=args.log)

    print(Fore.YELLOW + "\n⚠️ Se algum e-mail ou senha estiver 'Vazado', troque sua senha e ative MFA!")
    print(Fore.CYAN + "\n👉 Siga @CHDEVSEC para mais conteúdos de Segurança!")

if __name__ == "__main__":
    main()