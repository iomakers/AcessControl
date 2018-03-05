# Problemática

Sistemas de segurança e controle de acesso a locais restritos.

# Lista de Material

* Esp12
* Sensor de cartão RFID ou sensor Digital
* Computador
* Roteador
* Quadro elétrico
* Trilho Din
* Caneleta
* Fechadura Elétrica


# AcessControl

Sistema de controle de acesso usando o Esp12E, uma rest api usando Express e Supervisório ScadaBR

# Funcionamento do Sistema

O esp12E recebe o sinal do cartão RFID ou Sinal de digital, envia o dado para o servidor, se conferir abre a porta da sala e envia esse dado para o supervisório.



# Referências 

(Passport Bearer Token)[https://github.com/jaredhanson/passport-http-bearer]
(Passport basic strategy)[https://github.com/jaredhanson/passport-http]
(Example with express)[https://github.com/passport/express-4.x-http-bearer-example]
(HTTP client with header)[https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266HTTPClient/examples/Authorization/Authorization.ino]
