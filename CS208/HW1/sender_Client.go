package main

import (
	"fmt"
	"io"
	"net"
	"os"
)

func sendFile(conn net.Conn, filePath string) {
	//只读打开文件
	file, err := os.Open(filePath)
	if err != nil {
		fmt.Printf("os.Open() Err:%v\n", err)
		return
	}
	defer file.Close()

	buf := make([]byte, 4096)
	for {
		//从本地文件中读数据，写给网络接收端。读多少，写多少
		n, err := file.Read(buf)
		if err != nil {
			if err == io.EOF {
				fmt.Printf("Finished Sending\n")
			} else {
				fmt.Printf("file.Read() Err:%v\n", err)
			}
			return
		}
		//写到网络socket中
		_, err = conn.Write(buf[:n])
	}
}

func main() {

	//获取命令行参数
	list := os.Args

	if len(list) != 2 {
		fmt.Printf("go run  [].go [filename]\n")
		return
	}

	//提取文件的绝对路径
	path := list[1]

	//获取文件属性
	fileInfo, err := os.Stat(path)
	if err != nil {
		fmt.Printf("os.Stat()Err :%v\n", err)
		return
	}

	//主动发起连接请求
	conn, err := net.Dial("tcp", "127.0.0.1:8003")
	if err != nil {
		fmt.Printf("net.Dial()Err :%v\n", err)
		return
	}
	defer conn.Close()

	//发送文件名给接收端
	_, err = conn.Write([]byte(fileInfo.Name()))

	//读取服务器回发数据
	buf := make([]byte, 4096)
	n, err := conn.Read(buf)
	if err != nil {
		fmt.Printf("conn.Read(buf)Err :%v\n", err)
		return
	}

	if string(buf[:n]) == "ok" {
		//写文件内容给服务器 -- 借助conn
		sendFile(conn, path)
	}
}
