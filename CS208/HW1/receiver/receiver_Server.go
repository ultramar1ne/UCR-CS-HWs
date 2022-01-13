package main

import (
	"fmt"
	"io"
	"net"
	"os"
)

func recvFile(conn net.Conn, fileName string) {
	//按照文件名创建新文件
	file, err := os.Create(fileName)
	if err != nil {
		fmt.Printf("os.Create() Err:%v\n", err)
		return
	}
	defer file.Close()

	//从网络中读数据，写入本地文件
	for {
		buf := make([]byte, 4096)
		n, err := conn.Read(buf)

		//写入本地文件，读多少，写多少
		file.Write(buf[:n])
		if err != nil {
			if err == io.EOF {
				fmt.Printf("Finished Receving!\n")
			} else {
				fmt.Printf("conn.Read() Err:%v\n", err)
			}
			return
		}
	}
}

func main() {

	//1.创建监听socket
	listener, err := net.Listen("tcp", "127.0.0.1:8003")
	if err != nil {
		fmt.Printf("net.Listen()Err :%v\n", err)
		return
	}
	defer listener.Close()

	//阻塞监听
	conn, err := listener.Accept()
	if err != nil {
		fmt.Printf("listener.Accept()Err :%v\n", err)
		return
	}
	defer conn.Close()

	//文件名的长度不能超过1024个字节
	buf := make([]byte, 4096)
	n, err := conn.Read(buf)
	if err != nil {
		fmt.Printf("conn.Read()Err :%v\n", err)
		return
	}
	fileName := string(buf[:n-4]) + "_client_copy.txt"

	//回写ok给发送端
	conn.Write([]byte("ok"))

	//获取文件内容
	recvFile(conn, fileName)
}
