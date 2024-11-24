#my.ini 添加
[mysqld]
skip_ssl
SHOW VARIABLES LIKE '%ssl%';
use mysql;
alter user 'root'@'localhost' identified with mysql_native_password by '1234';