---
noteId: "1e5cbb304e2d11ea8720e7849bd662eb"
tags: []

---


### MySQL 基本语法：  
- 打开 MySQL 服务  
sudo service mysql start   
- 使用 root 用户登录，+密码  
mysql -u root -p+password  

#### 在 MySQL 控制台中输入命令，搭建数据库：  
- 进入sql服务后首先查看有哪些数据库  
show databases;  
- 若没有新建一个  
CREATE DATABASE demo_test;  
- 使用数据库  
use demo_test;  

#### 新建表并使用查看  
- 查看有哪些表  
show tables;  
- 新建表：CREATE TABLE xxxx();  
--书：书名和作者  
CREATE TABLE book(name char(20),author char(20));  
--读者：人名、借书日期以及性别  
CREATE TABLE reader(name char(20),date int(10),sex char(5));  

- 查看表的内容：SELECT * FROM xxx;  
SELECT * FROM book;  
SELECT * FROM reader;  
  
- 插入内容到表：INSERT INTO xxx VALUES();  
INSERT INTO 表名称 VALUES (值1, 值2,....);  
INSERT INTO table_name (列1, 列2,...) VALUES (值1, 值2,....);  
>eg:  
INSERT INTO book VALUES('c language','niuren')  
INSERT INTO book VALUES('java','lihairen')，('python','yjj')  
 
- INSERT INTO reader VALUES('kumata',20180530,'man');  
INSERT INTO reader(name,sex) VALUES('kusada','man');  
INSERT INTO reader(name,date) VALUES('wuyifan',20187475);  
 
- 再查看 即可显示已添数据  
SELECT * FROM book;  
SELECT * FROM reader;  

#### 查询数据表  
- 参考： https://www.w3school.com.cn/sql/index.asp  
- SQL SELECT 语句  
SELECT 列名称 FROM 表名称  
SELECT * FROM 表名称  
>eg:  
如需获取名为 "LastName" 和 "FirstName" 的列的内容（从名为 "Persons" 的数据库表）:  
SELECT LastName,FirstName FROM Persons;  
从 "Persons" 表中选取所有的列:  
SELECT * FROM Persons;  

- WHERE 子句  
有条件地从表中选取数据，可将 WHERE 子句添加到 SELECT 语句:  
SELECT 列名称 FROM 表名称 WHERE 列 运算符 值  

>eg:  
只希望选取居住在城市 "Beijing" 中的人...:  
SELECT * FROM Persons WHERE City='Beijing';  
SELECT * FROM Persons WHERE FirstName='Bush';  
SELECT * FROM Persons WHERE Year>1965;  

- AND 和 OR 运算符  
在 WHERE 子语句中把两个或多个条件结合起来  
SELECT * FROM Persons WHERE FirstName='Thomas' AND LastName='Carter';  
SELECT * FROM Persons WHERE firstname='Thomas' OR lastname='Carter';  
SELECT * FROM Persons WHERE (FirstName='Thomas' OR FirstName='William') AND LastName='Carter'  

### 修改表中数据  
- Update 语句  
UPDATE 表名称 SET 列名称 = 新值 WHERE 列名称 = 某值  
>eg:更新某一行中的一个列:  
UPDATE Person SET FirstName = 'Fred' WHERE LastName = 'Wilson';  
>eg:更新某一行中的若干列:  
UPDATE Person SET Address = 'Zhongshan 23', City = 'Nanjing' WHERE LastName = 'Wilson';  

#### 删除数据  
- 删除数据表：  
DROP TABLE xxx(table_name);  

- DELETE 语句：删除表中的行:  
DELETE FROM 表名称 WHERE 列名称 = 值;  
>eg:   
DELETE FROM Person WHERE LastName = 'Wilson'   
  
- 删除所有数据行，保留表的结构、属性和索引:  
DELETE FROM table_name;  
DELETE * FROM table_name;  

#### 导出、导入数据库文件  
- 导出表存储为sql文件规则  
mysqldump -u userName -p 源数据库 > 目标目录中的.sql文件;  

- 导入sql文件命令规则  
mysql -u userName -p 目标数据库 < 源sql文件路径;  
----  


----  
1、添加用户设置权限  
进入数据库  
mysql -uroot -p[password]  
>eg:  
root登录mysql,添加新用户comoon（用户名）,密码为空（自定义设置）;  
insert into mysql.user (Host,User, Password) values("%", "comoon", "");  

2、设置数据库使用权限（测试数据库是mysql_cpp_data）  
grant all privileges on mysql_cpp_data.* to comoon@localhost identified by '';  

3、刷新权限
flush privileges;  

4、g++ 编译
cd src  
g++ -o test1 demo1.cpp -I /usr/include/mysql++/ -I /usr/include/mysql -lmysqlpp  
g++ -o test2 demo2.cpp -I /usr/include/mysql++/ -I /usr/include/mysql -lmysqlpp  
g++ -o test3 demo3.cpp -I /usr/include/mysql++/ -I /usr/include/mysql -lmysqlpp -lmysqlclient  

5、cmake 编译
mkdir build  
cd build  
cmake ..  
make  
cd ../bin  
