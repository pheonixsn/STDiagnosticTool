STDiagnostic Tool 工程说明

1：目录结构：

├─AlgoCoreSmoke              					VSV算法库，仅包含需要引用的头文件
│  ├─InterfaceDecl
│  ├─VA
│  └─VSD
├─Debug_half													debug输出目录，config,event,screenshot均为算法配置目录，不要修改！！！！
│  ├─config
│  │  └─algocfg
│  ├─event
│  └─screenshot
├─opencv                              openccv依赖库
│  └─build
│      ├─include
│      │  ├─opencv
│      │  └─opencv2
│      │      ├─calib3d
│      │      ├─contrib
│      │      ├─core
│      │      ├─features2d
│      │      ├─flann
│      │      ├─gpu
│      │      │  └─device
│      │      │      └─detail
│      │      ├─highgui
│      │      ├─imgproc
│      │      ├─legacy
│      │      ├─ml
│      │      ├─nonfree
│      │      ├─objdetect
│      │      ├─ocl
│      │      ├─photo
│      │      ├─stitching
│      │      │  └─detail
│      │      ├─ts
│      │      ├─video
│      │      ├─videostab
│      │      └─world
│      └─x86
│          └─vc10
│              └─lib
├─Release_half                        release版本输出目录
│  ├─Config
│  │  └─algocfg
│  ├─Event
│  └─Screenshot
└─STEvaluation                        主工程目录
    ├─Debug_half
    └─res

2：工程采用VC2010 SP1编译通过，WIN7 32bit or 64bit。 注意：一定要打SP1补丁！！！！！！！！！！！

3：依赖MS VFW API，需确认系统支持。

4：工程使用opencv V2.4.3版本，请不要修改opencv目录下内容。

5：