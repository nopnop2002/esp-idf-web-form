# esp-idf-web-form
WEB Form example for ESP-IDF.   
ESP-IDF contains a lot of example code, but there is no example to create FORM on the WEB and input data from FORM.   
This project reads value from FORM on the WEB and save in the NVS area.   
No library other than ESP-IDF is required to read the data from the WEB page.   

I referred [here](https://github.com/espressif/esp-idf/tree/master/examples/protocols/http_server/file_serving).   

![Image](https://github.com/user-attachments/assets/342d2e60-c8b0-41bf-a7bd-1276a9c61932)

# Software requiment
ESP-IDF V5.0 or later.   
ESP-IDF V4.4 release branch reached EOL in July 2024.   
ESP-IDF V5.1 is required when using ESP32-C6.   

# Installation
```
git clone https://github.com/nopnop2002/esp-idf-web-form
cd esp-idf-web-form
idf.py menuconfig
idf.py flash monitor
```


# Configuration
Set the following items using menuconfig.

![config-main](https://user-images.githubusercontent.com/6020549/134126480-a1455518-e6c8-4897-a1e2-aec5dda50168.jpg)
![config-app](https://user-images.githubusercontent.com/6020549/134126500-cc609a2c-cc74-4eca-a5ad-359abe8cbe26.jpg)

## Wifi Setting

![config-wifi-1](https://user-images.githubusercontent.com/6020549/134127430-e55a9a9f-e3db-4766-a806-687ba58bad9a.jpg)

You can use the mDNS hostname instead of the IP address.   
![config-wifi-2](https://user-images.githubusercontent.com/6020549/134127158-892fac80-d123-4fd8-af16-f0b234a0efba.jpg)

You can use static IP.   
![config-wifi-3](https://user-images.githubusercontent.com/6020549/134127193-8bffe977-b4b8-4178-9810-06c99414055f.jpg)

## HTTP Server Setting
![config-http](https://user-images.githubusercontent.com/6020549/134127228-dbcdca4c-ea3a-45c8-82d2-5dbced108fe3.jpg)


# How to use
Open your brouser, and put address in address bar.   
You can use the mDNS hostname instead of the IP address.   
Default mDNS name is esp32-server.local.   
Input text/checkbox/radio and submit.   
The read data is saved in the NVS area.   
You can clear the NVS area with this command:   
```
idf.py erase_flash
```
![Image](https://github.com/user-attachments/assets/862645da-b884-4c60-a1db-2a5381f24894)
![Image](https://github.com/user-attachments/assets/342d2e60-c8b0-41bf-a7bd-1276a9c61932)

# HTML Header
HTML header is stored in html/head.html.   
You can use your favorite CSS.   

# How to browse image data using built-in http server   
Even if there are image files in SPIFFS, the esp-idf http server does not support this:   
```
httpd_resp_sendstr_chunk(req, "<img src=\"/spiffs/picture.png\">");
```

You need to convert the image file to base64 string.   
```
httpd_resp_sendstr_chunk(req, "<img src=\"data:image/png;base64,");
httpd_resp_sendstr_chunk(req, (char *)BASE64_ENCODE_STRING);
httpd_resp_sendstr_chunk(req, "\">");
```

Images in png format are stored in the image folder.   
Images in base64 format are stored in the html folder.   
I converted using the base64 command.   
```
$ base64 image/ESP-IDF.png > html/ESP-IDF.txt
```

# Reference
https://github.com/nopnop2002/esp-idf-pwm-slider

