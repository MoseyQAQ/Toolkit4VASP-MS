# Toolkit for VASP & Materials Studio
私人软件脚本库，写着玩玩；
有用的软件：
POT.c 生成POTCAR；（有bug，无法生成带有后缀POTCAR，已在python版本中修复）
psub.c psub-server.c psub.h psub-daemon.c 基于套接字和daemon的单机作业管理系统（偷懒版，最大队列50，以后更新链表等内容）
nebmake.py 基于ASE的过渡态结构生成脚本，支持IDPP和LI方法；
