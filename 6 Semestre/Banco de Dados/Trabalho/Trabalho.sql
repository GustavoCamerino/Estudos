-- MySQL dump 10.13  Distrib 8.0.36, for Linux (x86_64)
--
-- Host: localhost    Database: SAUDE
-- ------------------------------------------------------
-- Server version	8.0.42-0ubuntu0.22.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Consulta`
--

DROP TABLE IF EXISTS `Consulta`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Consulta` (
  `ID_Consulta` int NOT NULL,
  `Data` date NOT NULL,
  `Hora` time NOT NULL,
  `Status` varchar(20) NOT NULL,
  `CRM` varchar(10) NOT NULL,
  `CPF_Paciente` varchar(11) NOT NULL,
  `CPF_Recepcionista` varchar(11) NOT NULL,
  PRIMARY KEY (`ID_Consulta`),
  KEY `CRM` (`CRM`),
  KEY `CPF_Paciente` (`CPF_Paciente`),
  KEY `CPF_Recepcionista` (`CPF_Recepcionista`),
  CONSTRAINT `Consulta_ibfk_1` FOREIGN KEY (`CRM`) REFERENCES `Medico` (`CRM`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `Consulta_ibfk_2` FOREIGN KEY (`CPF_Paciente`) REFERENCES `Paciente` (`CPF`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `Consulta_ibfk_3` FOREIGN KEY (`CPF_Recepcionista`) REFERENCES `Recepcionista` (`CPF_Recepcionista`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `Consulta_chk_1` CHECK ((`Status` in (_utf8mb4'agendada',_utf8mb4'concluida',_utf8mb4'cancelada')))
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Consulta`
--

LOCK TABLES `Consulta` WRITE;
/*!40000 ALTER TABLE `Consulta` DISABLE KEYS */;
INSERT INTO `Consulta` VALUES (1,'2025-05-01','10:00:00','concluida','CRM1234','12345678901','11122233344'),(2,'2025-05-01','11:00:00','agendada','CRM5678','98765432109','11122233344'),(3,'2025-05-02','14:00:00','concluida','CRM1234','45678912345','11122233344');
/*!40000 ALTER TABLE `Consulta` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Consulta_Procedimento`
--

DROP TABLE IF EXISTS `Consulta_Procedimento`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Consulta_Procedimento` (
  `ID_Consulta` int NOT NULL,
  `Codigo_Procedimento` varchar(10) NOT NULL,
  `Observacoes` text,
  PRIMARY KEY (`ID_Consulta`,`Codigo_Procedimento`),
  KEY `Codigo_Procedimento` (`Codigo_Procedimento`),
  CONSTRAINT `Consulta_Procedimento_ibfk_1` FOREIGN KEY (`ID_Consulta`) REFERENCES `Consulta` (`ID_Consulta`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `Consulta_Procedimento_ibfk_2` FOREIGN KEY (`Codigo_Procedimento`) REFERENCES `Procedimento` (`Codigo_Procedimento`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Consulta_Procedimento`
--

LOCK TABLES `Consulta_Procedimento` WRITE;
/*!40000 ALTER TABLE `Consulta_Procedimento` DISABLE KEYS */;
INSERT INTO `Consulta_Procedimento` VALUES (1,'P001','Raio-X toracico'),(1,'P003','Consulta inicial'),(3,'P002','Hemograma completo'),(3,'P003','Consulta de acompanhamento');
/*!40000 ALTER TABLE `Consulta_Procedimento` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Convenio`
--

DROP TABLE IF EXISTS `Convenio`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Convenio` (
  `Cod_Convenio` varchar(10) NOT NULL,
  `Nome` varchar(20) NOT NULL,
  `Percentual_Cobertura` decimal(5,2) NOT NULL,
  PRIMARY KEY (`Cod_Convenio`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Convenio`
--

LOCK TABLES `Convenio` WRITE;
/*!40000 ALTER TABLE `Convenio` DISABLE KEYS */;
INSERT INTO `Convenio` VALUES ('C001','Amil',80.00),('C002','Unimed',70.00);
/*!40000 ALTER TABLE `Convenio` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Medico`
--

DROP TABLE IF EXISTS `Medico`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Medico` (
  `CRM` varchar(10) NOT NULL,
  `Nome` varchar(30) NOT NULL,
  `Especialidade` varchar(30) NOT NULL,
  `Telefone` varchar(30) NOT NULL,
  PRIMARY KEY (`CRM`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Medico`
--

LOCK TABLES `Medico` WRITE;
/*!40000 ALTER TABLE `Medico` DISABLE KEYS */;
INSERT INTO `Medico` VALUES ('CRM1234','Dr. Carlos Almeida','Cardiologia','11977778888'),('CRM5678','Dra. Ana Costa','Pediatria','11999990000');
/*!40000 ALTER TABLE `Medico` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Paciente`
--

DROP TABLE IF EXISTS `Paciente`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Paciente` (
  `CPF` varchar(11) NOT NULL,
  `Nome` varchar(30) NOT NULL,
  `Data_Nascimento` date NOT NULL,
  `Telefone` varchar(30) NOT NULL,
  `Endereco` varchar(30) NOT NULL,
  `Cod_Convenio` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`CPF`),
  KEY `Cod_Convenio` (`Cod_Convenio`),
  CONSTRAINT `Paciente_ibfk_1` FOREIGN KEY (`Cod_Convenio`) REFERENCES `Convenio` (`Cod_Convenio`) ON DELETE SET NULL ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Paciente`
--

LOCK TABLES `Paciente` WRITE;
/*!40000 ALTER TABLE `Paciente` DISABLE KEYS */;
INSERT INTO `Paciente` VALUES ('12345678901','Joao Silva','1990-05-15','11987654321','Rua A, 123','C001'),('45678912345','Pedro Santos','1978-03-12','11955556666','Rua C, 789','C002'),('98765432109','Maria Oliveira','1985-10-20','11912345678','Rua B, 456',NULL);
/*!40000 ALTER TABLE `Paciente` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Pagamento`
--

DROP TABLE IF EXISTS `Pagamento`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Pagamento` (
  `ID_Pagamento` int NOT NULL,
  `ID_Consulta` int NOT NULL,
  `Valor` decimal(10,2) NOT NULL,
  `Forma_Pagamento` varchar(20) NOT NULL,
  `Status` varchar(20) NOT NULL,
  `Pagador` varchar(30) NOT NULL,
  PRIMARY KEY (`ID_Pagamento`),
  KEY `ID_Consulta` (`ID_Consulta`),
  CONSTRAINT `Pagamento_ibfk_1` FOREIGN KEY (`ID_Consulta`) REFERENCES `Consulta` (`ID_Consulta`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `Pagamento_chk_1` CHECK ((`Forma_Pagamento` in (_utf8mb4'cartao',_utf8mb4'dinheiro',_utf8mb4'boleto'))),
  CONSTRAINT `Pagamento_chk_2` CHECK ((`Status` in (_utf8mb4'pago',_utf8mb4'pendente',_utf8mb4'cancelado'))),
  CONSTRAINT `Pagamento_chk_3` CHECK ((`Pagador` in (_utf8mb4'paciente',_utf8mb4'convenio')))
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Pagamento`
--

LOCK TABLES `Pagamento` WRITE;
/*!40000 ALTER TABLE `Pagamento` DISABLE KEYS */;
INSERT INTO `Pagamento` VALUES (1,1,40.00,'cartao','pago','paciente'),(2,1,160.00,'boleto','pago','convenio'),(3,3,300.00,'dinheiro','pago','paciente');
/*!40000 ALTER TABLE `Pagamento` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Procedimento`
--

DROP TABLE IF EXISTS `Procedimento`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Procedimento` (
  `Codigo_Procedimento` varchar(10) NOT NULL,
  `Nome` varchar(50) NOT NULL,
  `Valor` int NOT NULL,
  `Tempo_Estimado` int NOT NULL,
  PRIMARY KEY (`Codigo_Procedimento`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Procedimento`
--

LOCK TABLES `Procedimento` WRITE;
/*!40000 ALTER TABLE `Procedimento` DISABLE KEYS */;
INSERT INTO `Procedimento` VALUES ('P001','Raio-X',150,30),('P002','Exame de Sangue',100,15),('P003','Consulta Geral',200,45);
/*!40000 ALTER TABLE `Procedimento` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Recepcionista`
--

DROP TABLE IF EXISTS `Recepcionista`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Recepcionista` (
  `CPF_Recepcionista` varchar(11) NOT NULL,
  `Nome` varchar(20) NOT NULL,
  `Telefone` varchar(20) NOT NULL,
  PRIMARY KEY (`CPF_Recepcionista`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Recepcionista`
--

LOCK TABLES `Recepcionista` WRITE;
/*!40000 ALTER TABLE `Recepcionista` DISABLE KEYS */;
INSERT INTO `Recepcionista` VALUES ('11122233344','Clara Mendes','11911112222');
/*!40000 ALTER TABLE `Recepcionista` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2025-05-15 15:52:56
