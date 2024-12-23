# 开发主机和开发板连接热点
nmcli dev wifi
nmcli dev wifi connect wifi_name password wifi_passwd
ip addr show wlan0

# ssh连接到开发机
ssh root@192.168.10.168

# 推送到开发机
scp -r /home/G31415/lab-2022-st/out root@192.168.10.168:/root/out/
scp -r /home/G31415/lab-2022-st/out root@192.168.10.168:/root/out/