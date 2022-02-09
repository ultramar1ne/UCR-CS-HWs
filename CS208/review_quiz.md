# 208 Midterm
## Guide

 - the questions will be conceptual in nature. 
1. Understand about all the different types of virtualization; 
2. the details regarding memory management, 
3. the way we can support virtualization (with translation, hardware support from processors, privileges), 
4. Xen, 
5. Containers and some of the details on how they are managed in Docker, 
6. Container Networking, Migration (steps, LAN, WAN migration etc). 
7. Please look through all the slides, and read the Xen paper, the original virtualization paper). No math problems. Brush up on the homeworks just a bit.

## 1. types of vir
Software/Platform Infrasturcture as a Service (XaaS)

VMM:A flexible and programmable software layer called the Virtual Machine Monitor (VMM) or the hypervisor 

![](http://152.136.116.14:1023//uploads/upload_f009cdc751d1ee28869cc1219d3abdc0.png)


## 2. Memory Manage

### 2.1 memory vir
![](http://152.136.116.14:1023//uploads/upload_7885ff51044cf9884dc795c1b33c797d.png)

### 2.2 Mem Mange on Xen
![](http://152.136.116.14:1023/uploads/upload_c636a0671bed00c00333d42c39473eaa.png)

### 2.3 shadow page table
![](http://152.136.116.14:1023/uploads/upload_3ec593c41dcf9936556de890c76c6ab4.png)

shadow page table:  Guest Virtual table ->(G Physcial T-> Host VT)-> HPT

#### building
Problem: how can the VMM maintain consistent  shadow pages tables?
![](http://152.136.116.14:1023/uploads/upload_6d0bdce043207fd2ce60ad394123478b.png)

## 3. the way we can support virtualization (with translation, hardware support from processors, privileges), 
(ring: 0~5   0/3)
### 3.1 Native VMM
eg: VMWare 需要 Translation If sensitive instructions, replace by VMware procedure ——Binary translation

*Unmodified* OS is running in user mode

- But it thinks it is running in kernel mode (virtual kernel mode)
- privileged instructions trap; sensitive inst-> use VT to trap
- Hypervisor is the “real kernel” 

### 3.2 Hyper
• Type 2 hypervisors can work without virtualization  technology (VT) support
– Sensitive instructions replaced by procedures emulating them.

### 3.3 Paravirtualization
Paravirtualization: **modify OS kernel** to replace all  sensitive instructions with hypercalls (different from 1&2)

## 4. Xen

## 5. Containers/Docker
![](http://152.136.116.14:1023/uploads/upload_89018951bef4634372b797216c2d6f4c.png)
![](http://152.136.116.14:1023/uploads/upload_9d48575b970aecc48ff07f2fdc03354f.png)

## 6. Migration
- A VM is really just (memory + CPU + disk) state

## Live Migration
SFC -> Scale Frequency Cost
![](http://152.136.116.14:1023/uploads/upload_0bbbba289fdb0e886ead8ddd9930ffee.png)
### Pre-Copy
#### 1) pre-copy
![](http://152.136.116.14:1023/uploads/upload_9402da7a6914a52ec21bab6180ff455e.png)
![](http://152.136.116.14:1023/uploads/upload_9f7dffd0dade64d64854d52036ab65cf.png)
#### 2) Managed Migration (XEN)
![](http://152.136.116.14:1023/uploads/upload_e7ff0f02cb29f6da63fa63236951376c.png)

#### 3) Self
![](http://152.136.116.14:1023/uploads/upload_088210a3f6a9c4f0abec752dd55f442a.png)
艹。这俩有啥区别？一个是read-only 一个是write-protect?？难道不是一回事？操他大爷


### Post-CP
pre有时候不太行啊，一直得resend dirty pages
![](http://152.136.116.14:1023/uploads/upload_966d242bbd63a423828b13485ba54285.png)


![](http://152.136.116.14:1023/uploads/upload_2e5603b36873d8cd6008b4d8f4c9539c.png)
准备阶段可以把最近常用的页都push过去，

### Hybrid Live Migration
![](/uploads/upload_08112643ece9afa01f1a79814c8d4e48.png)

## 7. Van
## 8. CNI
