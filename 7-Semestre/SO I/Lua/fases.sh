lua=("1F311"
      "1F312" 
      "1F313" 
      "1F314" 
      "1F315"
      "1F316"
      "1F317"
      "1F318")

while true; do
    for emoji in "${lua[@]}"
    do 
        printf "\r\U$emoji"
        sleep 0.15
done
done
