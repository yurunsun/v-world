#V-World开源项目

##1. 项目简介

###1.1 V-World Lib

V-World Lib 是一个使用OpenGL1.1实现的高性能3D图形库，用于快速开发Windows操作系统下交互式三维图形应用软件。

主要特性如下：

+ 向量、四元组、矩阵等数学库
+ 基本图元、模型文件图元
+ 由几何节点、灯光节点、照相机节点、组节点构成的场景图
+ 封装绘制与窗体
+ 接口与实现分离，易于使用
+ 引用计数管理内存

###1.2 VWViewer

VWViewer作为样例应用程序，使用V-World Lib实现了支持多种格式的3d模型查看器。

###1.3 开源许可证

上述项目均遵从于GNU公共许可证(LGPL)：允许在商业应用中动态链接。

###1.4 第三方库

+ 使用[lib3ds](http://code.google.com/p/lib3ds/)帮助处理3ds文件

+ 使用[glm](http://www.pobox.com/~ndr/)帮助处理obj文件

+ 使用[WTL](http://sourceforge.net/projects/wtl/)帮助处理Win32 API

###1.5 加入项目

+ 项目主页：[https://code.google.com/p/v-world/](https://code.google.com/p/v-world/)

+ SVN: [https://v-world.googlecode.com/svn/trunk/](https://v-world.googlecode.com/svn/trunk/)

+ 提交bug或希望加入请联系：[yurunsun@gmail.com](mailto:yurunsun@gmail.com)

##2. 编译运行

###2.1 编译

+ 安装VS2010(Express版除外,因为其不包含atl等模板库)

+ 到[WTL](http://sourceforge.net/projects/wtl/)项目主页，或者直接checkout WTL模板库：[svn://svn.code.sf.net/p/wtl/code/](svn://svn.code.sf.net/p/wtl/code/)

+ 打开checkout的WTL项目目录，将`\wtl\trunk\wtl\include\`目录下所有头文件复制到安装VS2010时创建的Microsoft SDK头文件目录，例如：

		D:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\atlmfc\include\

+ 使用VS2010打开`VirtualWorld.sln`，编译

###2.2 运行

Debug与Release模式下编译的目标文件分别放置于`\BinDebug\`与`\BinRelease\`目录。其中VirtualWorld.dll为V-World lib, VWViewer.exe为使用V-World库开发的示例程序：3D模型查看器

![](http://img.blog.csdn.net/20130625222640312?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvc3VueXVydW4=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)

##3. 使用V-World Lib开发图形软件

下面以VWViewer为例介绍如何使用V-World Lib开发交互式图形软件。

###3.1 创建应用项目

V-World Lib为使用者提供了一个以ATL的`CWindow`为基类的窗口类，能够作为Frame风格的窗口独立展示，也能作为子窗口轻易地嵌入MFC/WTL/ATL/Win32/Qt等任何框架产生的窗口中，因此应用程序的类型非常自由。在VWViewer中我们使用了WTL的VS插件自动生成了带菜单栏的Frame风格的主窗口。

###3.2 配置应用项目

+ 添加头文件

	V-World Lib特点之一是实现与接口分离，只需要一个头文件(外加.inl文件提供内联函数实现）与一个库文件。头文件中定义了所需要的接口类，除一些getter/setter为提供高效率使用内联实现外，其余均使用纯虚函数作为接口存在。

		打开应用项目配置页 -> Configuration Properties -> VC++ Directories -> Include Directories

	添加

		..\VirtualWorld\Include;

+ 添加库文件

	推荐使用动态链接的方式使用V-World。在编译时有两种方式寻找动态链接库的函数地址，一种是在代码中显示使用`LoadLibrary`等API，另一种是链接伴随动态链接库产生的.lib文件。（注意这里的.lib仅为了寻找dll地址而存在，不要与静态链接方式混淆。）我们选择后者这种方式：

		打开应用项目配置页 -> Configuration Properties -> VC++ Directories -> Library Directories

	添加

		..\VirtualWorld\BinDebug

	如果是Release的配置则改为

		..\VirtualWorld\BinRelease;

	然后

		打开应用项目配置页 -> Configuration Properties -> Linkder -> Input

	添加`VirtualWorld.lib`

接下来请打开`..\VirtualWorld\Include\VirtualWorld.h`文件，来查看可以使用的类库。

###3.3 使用工厂类`CFactory`创建实例

	namespace VirtualWorld 
	{
		class VIRTUALWORLD_API CFactory 
			: public CSingleton<CFactory>
		{
		public:
			IWindow32*					CreateWindow32();
			//...
		};
	}

头文件中定义的大部分类都需要使用工厂类创建实例，这是实现与接口分离常用的模式。

另一方面工厂类作为单例存在也是约定俗成的模式之一。

例如想要创建IWindow32对象：

	IWindow32* pView = VirtualWorld::CFactory::GetInstance()->CreateWindow32();

###3.4 使用窗口类`IWindow32`创建窗口

熟悉Win32 API的读者会发现`IWindow32`定义了一些Windows风格的函数接口，这是因为V-World Lib并没有准备跨平台。

***方法：***

+ `CreateWin(...)`：与标准Win32 API中`CreateWindow`函数具有相同的参数

+ `GetHwnd()`：获取窗口句柄

+ `RedrawWin(...)`：与标准Win32 API中`RedrawWindow`函数具有相同的参数

+ `PreTranslateMessage(...)`：MFC风格的消息预处理函数

***属性：***

+ `RootSGNode`：场景图的根节点（后续介绍）

+ `ActiveCameraNode`：激活状态的照相机（后续介绍）

+ `GUIEventHandler`：GUI事件回调接口（后续介绍）

具体应用：

1. 在WTL生成的主窗口类中添加IWindow32作为成员：

		VirtualWorld::IWindow32*	m_pView;

2. 在WTL生成的主窗口类的`WM_CREATE`响应函数`OnCreate`中创建子窗口：

		m_pView = pFac->CreateWindow32();
		m_hWndClient = m_pView->CreateWin(m_hWnd, rcDefault, NULL, 
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);
		m_pView->SetGUIEventHandler(this);

现在我们已经成功调用V-World中IWindow32接口创建了子窗口。

###3.5 使用场景图相关类创建场景节点

####3.5.1 场景图的概念

在刚刚的`IWindow32`接口中提到了存取场景图根节点的两个函数，下面解释场景图的相关概念。

数据结构角度讲，场景是一个DAG图，称为Scene Graph，简称SG. 场景的绘制就是对SG各个节点的遍历绘制。节点分为组节点和叶子节点两类，下边伪代码展示了一份可能的、合理的调用顺序：
	
	// 这里有我自己
	LeafNode* myself = new LeafNode;
	
	// 左侧有一个车一只狗
	LeafNode* car = new LeafNode;
	LeafNode* dog = new LeafNode;
	GroupNode* leftside = new GroupNode;
	leftside->addChild(car);
	leftside->addChild(dog);
	
	// 远处有一个操场和足球
	LeafNode* football = new LeafNode;
	LeafNode* grassland = new LeafNode;
	GroupNode* faraway = new GroupNode;
	faraway->addChild(football);
	faraway->addChild(grassland);

	// 这三组事务构成一幅图
	GroupNode* root = new GroupNode;
	root->addChild(leftside);
	root->addChild(faraway);
	root->addChild(myself);

####3.5.2 节点基类`ISceneBaseNode`

该类是所有场景节点的基类。

***属性：***

+ Name：节点名字
+ Parent：父节点指针
+ NodeType：节点类型
+ NodeTypeString：字符串版本的节点类型
+ Visibility：可见
+ LocalMatrix：局部坐标系下的变换矩阵
+ WorldMatrix：世界坐标系下的变换矩阵

局部坐标系初始为4*4单位矩阵，世界坐标系下的变换矩阵相当于父节点的世界坐标系下变换矩阵，乘以自身局部坐标系下的变换矩阵：

	this->WorldMatrix = parent->WorldMatrix * this->LocalMatrix

另外需要注意的是，节点是以名字作为key存储在其父节点提供的map容器中的，因此所有节点必须有名字，否则无法依附到父节点上。

***方法：***


	Translate(const CVector3f& t);
	Rotate(float angle, const CVector3f& axis);
	Scale(const CVector3f& axis);

分别表示该节点在局部坐标系下的平移、旋转、缩放，实际效果直接作用在当前节点的局部坐标变换矩阵上。举例说明：

初始情况下节点局部坐标变换矩阵 L = I，为单位矩阵；
移动到(1.0f, 2.0f, 3.0f)位置上的时候，创建位移矩阵T:

		1 0 0 0
	T = 0 1 0 0
     	0 0 1 0
		1 2 3 1

此时

	L = L * T = I * T;

再沿xyz轴做如下缩放(2.0f, 5.0f, 0.5f)，即沿x轴放大2倍，y轴放大5倍，z轴缩小为原来0.5倍，则创建缩放矩阵R

		2 0 0 0
	R = 0 5 0 0
     	0 0 0.5 0
		0 0 0 1

此时

	L = L * R = I * T * R

####3.5.3 组节点`ISceneGroupNode`

除了`ISceneBaseNode`提供的属性和方法外，主要负责管理子节点：
	
	typedef std::map<CString, ISceneBaseNode*> NodeTable;
	void AddChild(ISceneBaseNode* a_Child);
	ISceneBaseNode*	GetChild(const CString& a_Name) const;
	const NodeTable& GetChildren() const;
	void RemoveChild(ISceneBaseNode* a_Child);
	void RemoveChild(const CString& a_Name);
	
使用map管理子节点是经典模式之一，不做累述。

####3.5.4 图元节点`ISceneGeometryNode`

除了`ISceneBaseNode`提供的属性和方法外，新增`GeometryObject`属性，即将某图元依附到图元节点上。`GeometryObject`会在后续介绍。

####3.5.5 光照节点`ISceneLightNode`

除`ISceneBaseNode`提供的属性方法外，新增光照相关属性如下：

	ID;
	Ambient;
	Diffuse;
	Specular;
	Position;
	SpotDirection;
	SpotExponent;
	SpotCutoff;
	Attenuation;

这些是经典的光照参数，可以参阅图形学教材进一步了解。

####3.5.6 相机节点`ISceneCameraNode`

新增属性如下：

	Fovy;
	ZNear;
	ZFar;
	Rect;

这些是经典的调整视角、裁剪平面、视口大小的参数。

新增方法：

CameraNode中新增方法有些特殊：

	void LookAt(const CVector3f& a_Position, const CVector3f& a_FocusPoint, const CVector3f& a_UpVector);
		
这是除`ISceneBaseNode`中提供的三个仿射变换外，另一个能作用于变换矩阵的函数，熟悉opengl的读者立即会发现此函数类似于opengl中经典的

	gluLookAt(...);

这里的`LookAt`会修改`LocalMatrix`，完成坐标系变换。

####3.5.7 相机节点是否添加到根节点下

玩过游戏的读者都知道游戏中有多种视角，例如CS游戏中第一人称视角时，照相机显然要随人物节点而移动。这时显然将相机节点与图元节点一起作为子节点显得合理。但当游戏挂了之后CS允许使用自由视角，这时可以不必将相机节点加入到场景图中，从而在世界坐标系下更方便的对相机进行变换。

无论何时只能有一个处于激活状态的照相机，这就是为什么`IWindow32`中提供了`ActiveCamera`属性。


###3.6 几何图形

在3.5.4中我们提到了图元节点使用`GeometryObject`属性作为几何图形，反过来每个`GeometryObject`需要依附在`ISceneGeometryNode`节点出现在场景图中。

####3.6.1 `IGeometryBaseObject`

所有几何图形类的基类。

***属性:***

+ `DrawMode`：以填充方式还是轮廓线方式绘制图形
+ `NormalMode`：顶点法线还是面法线
+ `GetBoundingBox`：包围盒
+ `Material`：材料

####3.6.2 常见图形

与glu/glut/qgl等库类似，这里提供了基本图形：

+ `IGeometryCubeObject`：立方体
+ `IGeometrySphereObject`：球体
+ `IGeometryCylinderObject`：圆柱体

####3.6.3 从模型文件中获取图形

`IGeometryModelObject`新增的方法为

	bool LoadModel(const CString& a_FileName);

在使用工厂函数创建此实例时，会根据文件类型（.obj, .3ds, .dae, .3dxml,...等)创建不同的实例。调用示例如下：

	CString modelType = CUtility::GetFileSuffix(a_FilePath);
	IGeometryModelObject* objModel = CFactory::GetInstance()->CreateGeometryModelObject(modelType);
	if (objModel != NULL) {
		bool hr = objModel->LoadModel(a_FilePath);
		if (hr == true)  {
			//...
		}
	}

目前实现了obj与3ds文件的支持。

###3.7 完整实例

以下是在VWViewer中调用V-Model的示例代码，完整代码请参阅`MainFrm.cpp`.

	LRESULT CMainFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CFactory* pFac = CFactory::GetInstance();
	
		m_pView = pFac->CreateWindow32();
		m_hWndClient = m_pView->CreateWin(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);
		m_pView->SetGUIEventHandler(this);
		m_pCameraDlg = new CCameraDlg();
		m_pCameraDlg->Create(m_hWnd);
		m_pNodetreeDlg = new CNodetreeDlg();
		m_pNodetreeDlg->Create(m_hWnd);
		
		ISceneGroupNode* rootNode = pFac->CreateSceneGroupNode();
		ISceneCameraNode* cameraNode = pFac->CreateSceneCameraNode();
		ISceneGeometryNode* cubeNode = pFac->CreateSceneGeometryNode();
		ISceneGeometryNode* sphereNode = pFac->CreateSceneGeometryNode();
		ISceneGeometryNode* cylinderNode = pFac->CreateSceneGeometryNode();
		ISceneLightNode* lightNode = pFac->CreateSceneLightNode();
	
		IGeometryCubeObject* cubeObj = pFac->CreateGeometryBoxObject();
		IGeometrySphereObject* sphereObj = pFac->CreateGeometrySphereObject();
		IGeometryCylinderObject* cylinderObj = pFac->CreateGeometryCylinderObject();
	
		IMaterial* material = pFac->CreateMaterial();
		material->SetAmbient(CVector4f(0.000f, 0.50f, 0.000f, 1.0f));
		material->SetDiffuse(CVector4f(0.000f, 0.300f, 0.000f, 1.0f));
		material->SetSpecular(CVector4f(1.000f, 1.000f, 1.000f, 1.0f));
		material->SetEmmision(CVector4f(0.000f, 0.000f, 0.000f, 1.0f));
		material->SetShine(128.000f);
	
		cubeObj->SetMaterial(material);
		cubeObj->SetRadius(0.3f);
		cubeObj->SetDrawMode(IGeometryBaseObject::GEOMETRY_DRAW_SOLID);
		cubeNode->SetName(_T("Box1"));
		cubeNode->SetGeometryObject(cubeObj);
		cubeNode->Translate(CVector3f(1.0f, 0.0f, 0.0f));
		rootNode->AddChild(cubeNode);
	
		sphereObj->SetMaterial(material);
		sphereObj->SetRadius(0.4f);
		sphereObj->SetDrawMode(IGeometryBaseObject::GEOMETRY_DRAW_SOLID);
		sphereObj->SetNormalMode(IGeometryBaseObject::GEOMETRY_NORMAL_VERTEX);
		sphereNode->SetName(_T("Sphere1"));
		sphereNode->SetGeometryObject(sphereObj);
		sphereNode->Translate(CVector3f(-1.0f, 0.0f, 0.0f));
		rootNode->AddChild(sphereNode);
	
		cylinderObj->SetMaterial(material);
		cylinderObj->SetDrawMode(IGeometryBaseObject::GEOMETRY_DRAW_SOLID);
		cylinderObj->SetNormalMode(IGeometryBaseObject::GEOMETRY_NORMAL_VERTEX);
		cylinderObj->SetBaseRadius(0.3f);
		cylinderNode->SetName(_T("Cylinder1"));
		cylinderNode->SetGeometryObject(cylinderObj);
		cylinderNode->Translate(CVector3f(0.0f, 0.0f, -1.0f));
		cylinderNode->Rotate(0.1f, CVector3f(1.0f, 0.0f, 0.0f));
		rootNode->AddChild(cylinderNode);
	
		lightNode->SetName(_T("light0"));
		lightNode->SetAmbient(CVector4f(0.4f, 0.4f, 0.4f, 1.0f));
		lightNode->SetPosition(CVector4f(-1.0f, -1.0f, 1.0f, 0.0f));
		rootNode->AddChild(lightNode);
	
		cameraNode->SetName(_T("Camera"));
		cameraNode->SetFovy(30.0f);
		cameraNode->SetZNear(1.0f);
		cameraNode->SetZFar(1000.0f);
		cameraNode->Translate(CVector3f(0.0f, 0.0f, 5.0f));
	
		rootNode->SetName(_T("Root"));
		m_pView->SetActiveCameraNode(cameraNode);
		m_pView->SetRootSGNode(rootNode);
	
		// register object for message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->AddMessageFilter(this);
		pLoop->AddIdleHandler(this);
	
		return 0;
	}


##4. V-Model的架构设计

V-Model从逻辑上从底到上分为四层：

+ 数学类
+ 图形类
+ 节点类
+ 窗口类

其中数学类有CVector3, CVector4, CMatrix，包含了大量数学运算；

图形类一部分提供了基本图形，一部分用于加载模型文件；绘制时均使用opengl1.1中的显示列表技术提高渲染效率；

节点类逻辑清晰地组织场景，将易于出错的世界坐标系、局部坐标系、仿射变换等概念化简为父子关系；

窗口类则封装了Windows窗口，组织根节点与摄像机，同时提供GUI事件回调接口。

一般用户可以使用V-Model来快速处理3d模型文件，并组织场景进行绘制；感兴趣的读者可以申请加入此项目，扩展支持的文件格式，修改bug等；对于VWViewer，也欢迎对此产品有创意和想法的朋友加入进来。


----
+ 如果这篇文章对您有帮助，请到[CSDN博客](http://blog.csdn.net/sunyurun)留言；
+ 转载请注明：来自[雨润的技术博客](http://blog.csdn.net/sunyurun) http://blog.csdn.net/sunyurun










