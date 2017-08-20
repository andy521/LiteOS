### 安装[mosca](https://github.com/mcollina/mosca)
```sh
cnpm install mosca --save
```
#### 注：必须安装python2.7才能够正常安装

### 运行
```sh
node mqtt_server.js
```

### 安装[mongod](https://www.mongodb.com/)数据库

#### 1. 下载安装包:https://www.mongodb.com/download-center#community
#### 2. 创建数据目录
```sh
cd d:
mkdir mongod
cd mongod
mkdir db
mkdir dbConf
```
#### 3. 命令提示符下运行 MongoDB 服务器.指定数据库的文件夹
```sh
mongod --dbpath d:\mongod\db
```
#### 4. 将MongoDB服务器作为Windows服务运行
```sh
mongod.exe --bind_ip 192.168.0.11 --logpath "D:\mongod\dbConf\mongodb.log" --logappend --dbpath "D:\mongod\db" --port 1883 --serviceName "mongodServiceName" --serviceDisplayName "mongodServiceName" --install
```

