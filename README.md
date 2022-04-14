# telegramBot-WebHook
This is an webserver to be used as a webhook for a Telegram Bot. It means it uses tlsv1.2 from openssl libraries. 
Since this is a self-signed HTTP webserver, the certificate has to be uploaded manually. You will find furthere information below.

## Getting started
### First step:
After running make, you are ready to go.
### Second Step in Terminal:
```javascript
var s = "JavaScript syntax highlighting";
alert(s);
```
- Go to sslkey folder
``` bash
cd https-webserver/server/sslkeys
```
- Edit the generator file with your information
``` bash
``` 
- Add execution feature to file
``` bash
chmod +x genkeys.sh˘˘ 
```
- Generate the private and public keys
``` bash
./genkeys.sh
```
- Go back to the server folder
``` bash
cd ../
``` 
- (Optional) start a screen
``` bash
screen
```
- On the new screen created, run the server
``` bash
sudo ./main
```

## Reqs
- openssl (libssl-dev)
- (optional) screen
