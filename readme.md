# 嵌入式实验

## 配置环境

### 开发主机和开发板连接热点

`nmcli dev wifi`

`nmcli dev wifi connect wifi_name password wifi_passwd`

`ip addr show wlan0`

### ssh连接到开发机
`ssh root@192.168.10.168`

### 推送到开发机
`scp -r /home/G31415/lab-2022-st/out root@192.168.10.168:/root/out/`

### 修改rules.mk

```makefile
$(EXENAME): $(EXEOBJS)
	$(CC) $(LDFLAGS) -o $(EXENAME) $(EXEOBJS) $(LIB)
	cp $(EXENAME) ../out/
	# scp -r $(EXENAME) root@192.168.10.168:/root/out/
```

去掉注释可以在编译时推送到开发板

## Lab1：简单linux应用程序开发

在Lab1中运行命令`make`，编译，推送

在远程终端运行 `./lab1`

![Clip_2024-12-23_15-38-46](./assets/Clip_2024-12-23_15-38-46.png)

## Labe2：Linux framebuffer显示界面开发



## Labe3：图片显示和文本显示



## Labe4：Linux touchscreen多点触摸开发



## Labe5：蓝牙无线互联通讯



## Labe6：综合实验



