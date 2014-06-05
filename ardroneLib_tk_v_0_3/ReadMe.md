#ARDrone SDK by tkorays

##文件说明
大部分为类文件，类名与文件名保持一致。其他为一些辅助的文件。

* basic_struct.h里面是一些基本结构体。
* comdef.h包含一些宏定义
* helper.h里面是一些辅助函数，包括ip获取，状态检查。


##类说明

下面是主要的类使用方法:

###ComandId
用于维护一个全局的AT指令id，主要函数有get_id(bool auto_inc)。
auto_inc如果为false，表示获取当前id，为true表示先将id自增再返回id。

###ATCmdGenerator
用于产生AT指令，主要函数cmd_*(...)。
可以用于指令打包，函数pack、clear、操作符<<等。
可以在这里获取最后一次获取cmd的CommandId值，get_current_id()。

###ATCmdClient
维护AT指令，其他线程可以通过获取其指针，给它分配指令任务。

成员变量cmd_list里面保存了指令序列。

###NavDataClient
维护navdata，初始化函数里面会给ATCmdClient分配任务。


##其他
详细介绍参考v_0_3_demo的例子。
