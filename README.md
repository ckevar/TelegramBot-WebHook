# telegramBot-WebHook
This is an webserver to be used as a webhook for a Telegram Bot. It means it uses tlsv1.2 from openssl libraries. 
Since this is a self-signed HTTP webserver, the certificate has to be uploaded manually. You will find furthere information below.

## Getting started
### First step:
After running make, you are ready to go.
### Second Step in Terminal:

- Go to sslkey folder
``` bash
$ cd https-webserver/server/sslkeys
```
- Open the generator bash to edit
``` bash
$ nano genkeys.sh
``` 
- Edit the generator bash with your information
``` bash

``` 
- Add execution feature to file
``` bash
$ chmod +x genkeys.sh˘˘ 
```
- Generate the private and public keys
``` bash
$ ./genkeys.sh
```
- Go back to the server folder
``` bash
$ cd ../
``` 
- (Optional) start a screen
``` bash
$ screen
```
- On the new screen created, run the server
``` bash
$ sudo ./main
```

## Reqs
- openssl (libssl-dev)
- (optional) screen
