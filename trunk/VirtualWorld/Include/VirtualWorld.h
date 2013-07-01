#pragma once

/**
 * Project:		Virtual World 3d model library
 *
 * Homepage:	http://code.google.com/p/yurun/
 * Author:		VirtualWorld develop team
 * Date:		2013-5-17
 * Version:		v0.1
 * Introduction:	
 * Statement:	You can use this code freely, and modify or add components at your pleasure, but please don't 
 *				erase this statement. Sharing your modified copy with me would be highly appreciated.
 *				It's not allowed to use for merchant purpose without contact with author.
 */

/** 
 * The following ifdef block is the standard way of creating macros which make exporting 
 * from a DLL simpler. All files within this DLL are compiled with the VIRTUALWORLD_EXPORTS
 * symbol defined on the command line. This symbol should not be defined on any project
 * that uses this DLL. This way any other project whose source files include this file see 
 * VIRTUALWORLD_API functions as being imported from a DLL, whereas this DLL sees symbols
 * defined with this macro as being exported.
 */
#ifdef VIRTUALWORLD_EXPORTS
#define VIRTUALWORLD_API __declspec(dllexport)
#else
#define VIRTUALWORLD_API __declspec(dllimport)
#endif

#include <atlbase.h>
#include <atltypes.h>
#include <atlstr.h>
#include <atlwin.h>
#include <cmath>
#include <map>

namespace VirtualWorld
{
	/**
	 * Template Singleton Class Interfaces all Singletons
	 */
	template <class T>
	class CSingleton
	{
	public:
		static T* GetInstance();

	protected:
		/* Hide constructor */
		CSingleton(){}
		virtual ~CSingleton(){}

	private:
		/* Non-copyable */
		CSingleton(const CSingleton&);
		CSingleton& operator = (const CSingleton& a_Other);
	};

	/**
	 * Base class to share instance object using reference counting
	 */
	class CSharedObject
	{
	public:
		CSharedObject() : m_Ref(0){}
		virtual ~CSharedObject(){}
		unsigned long AddRef();
		unsigned long Release();

	protected:
		unsigned long m_Ref;
	};

	
	/**
	 * Triple type with math operations. Used for color, point, etc.
	 */
	template <class T>
	class CVector3
	{
	public :
		union {
			struct {
				T x, y, z;
			};
			struct {
				T r, g, b;
			};
			T m_Values[3];
		};
		CVector3<T>	(T a_x = 0, T a_y = 0, T a_z = 0);
		CVector3<T>	(T a_xyz);
		CVector3<T>	(const CVector3<T>& a_Source);
									operator T* ();
									operator const T* () const;
		CVector3<T>&				operator = (const CVector3<T>& a_Right);
		CVector3<T>					operator + (const CVector3<T>& a_Right) const;
		CVector3<T>					operator - (const CVector3<T>& a_Right) const;
		CVector3<T>					operator * (const T a_Scale) const;
		CVector3<T>					operator / (const T a_Scale) const;
		CVector3<T>&				operator +=	(const CVector3<T>& a_Right);
		CVector3<T>&				operator +=	(const T a_xyz);
		CVector3<T>&				operator -=	(const CVector3<T>& a_Right);
		CVector3<T>&				operator -=	(const T a_xyz);
		CVector3<T>&				operator *=	(const T a_Scale);
		CVector3<T>&				operator /=	(const T a_Scale);
		bool						operator ==	(const CVector3 &a_Right);
		bool						operator !=	(const CVector3 &a_Right);
		const T						operator []	(unsigned i) const;
		      T&					operator []	(unsigned i);
		void						Set(const T x, const T y, const T z);
		void						Zero();
		CVector3<T>&				Normalize();
		const T						LengthSquared() const;
		const T						Length()        const;
		const T						DotProduct(const CVector3<T>& t) const;
		CVector3<T>&				CrossProduct(const CVector3<T>& t1, const CVector3<T>& t2);
	};

	typedef CVector3<int   >		CVector3i;
	typedef CVector3<float >		CVector3f;
	typedef CVector3<double>		CVector3d;

	/**
	 * Quaternion type with math operations. Used for color, point, etc.
	 */
	template <class T>
	class CVector4
	{
	public :
		union {
			struct {
				T x, y, z, w;
			};
			struct {
				T r,g,b,a;
			};
			T m_Values[4];
		};
									CVector4<T>	(T a_X = 0, T a_Y = 0, T a_Z = 0, T a_W = 1);
									CVector4<T>	(T a_XYZW);
									CVector4<T>	(const CVector4<T> &a_C);
									operator T* ();
									operator const T* () const;
		const T						operator [](unsigned int a_Index) const;
		T&							operator [](unsigned int a_Index);
		CVector4<T>&				operator = (const CVector4<T> &a_Source);
		CVector4<T>					operator + (const CVector4<T> &a_Right);
		CVector4<T>					operator - (const CVector4<T>  &a_Right);
		CVector4<T>					operator * (const T a_Scale);
		CVector4<T>					operator / (const T a_Scale);
		CVector4<T>&				operator += (const CVector4<T> &a_Right);
		CVector4<T>					operator -= (const CVector4<T> &a_Right);
		CVector4<T>					operator *= (const T a_Scale);
		CVector4<T>					operator /= (const T a_Scale);
		bool						operator == (const CVector4<T> &a_Right);
		bool						operator != (const CVector4<T> &a_Right);
		void						Set(T a_X = 0, T a_Y = 0, T a_Z = 0, T a_W = 1);
	};
	typedef CVector4<int   >		CVector4i;
	typedef CVector4<float >		CVector4f;
	typedef CVector4<double>		CVector4d;

	/**
	 * Matrix type with math operation like + - * / , and geometry operation like translate rotate and scale.
	 */
	template <class T>
	class CMatrix4
	{
	public:
		union {
			struct {
				T _11, _12, _13, _14;
				T _21, _22, _23, _24;
				T _31, _32, _33, _34;
				T _41, _42, _43, _44;
			};
			T m_Matrix[4][4];
			T m_Values[16];
		};
		CMatrix4(T a_Scale = 1);
		CMatrix4(const T* a_Elements);
		CMatrix4(const CMatrix4<T>& a_Matrix);
		CMatrix4(T  m0, T  m1, T  m2, T  m3,
				 T  m4, T  m5, T  m6, T  m7,
				 T  m8, T  m9, T m10, T m11,
				 T  m12,T m13, T m14, T m15);
		CMatrix4<T>					operator * (const CMatrix4<T>& a_Matrix) const;
		CMatrix4<T>					operator + (const CMatrix4<T>& a_Matrix) const;
		CMatrix4<T>					operator - (const CMatrix4<T>& a_Matrix) const;
		CMatrix4<T>&				operator +=(const CMatrix4<T>& a_Matrix);
		CMatrix4<T>&				operator -=(const CMatrix4<T>& a_Matrix);
		CMatrix4<T>&				operator *=(const T a_Value);
		CMatrix4<T>&				operator *=(const CMatrix4<T>& a_Matrix); 
		bool						operator ==(const CMatrix4<T>& a_Matrix);
		bool						operator !=(const CMatrix4<T>& a_Matrix);
		CMatrix4<T>&				operator = (const CMatrix4<T>& a_Matrix);
									operator const T*() const;
									operator T*() const;  
		void						Identity();
		void						IdentityRotate(T a_Angle, const CVector3<T>& a_Axis);
		void						IdentityScale(const CVector3<T>& a_Axis);
		void						IdentityTranslate(const CVector3<T>& a_Vector);
		void						Set(const CMatrix4<T>  &a_Matrix);
		void						Set(const T* a_Elements);
		void						Set(T  m0, T  m1, T  m2, T  m3,
										T  m4, T  m5, T  m6, T  m7,
										T  m8, T  m9, T m10, T m11,
										T  m12,T m13, T m14, T m15);
		void						Rotate(T a_Angle, const CVector3<T>& a_Axis);
		void						Scale(const CVector3<T>&  a_Axis);
		void						Translate(const CVector3<T>& a_Vector);
		CMatrix4<T>&				LookAt(const CVector3<T>& a_Position, const CVector3<T>& a_FocusPoint, const CVector3<T>& a_UpVector);
		CVector3f					RightVector() const;
		CVector3f					UpVector() const;
		CVector3f					ForwardVector() const;
		CVector3f					TranslationVector() const;
	};
	
	typedef CMatrix4<int   >		CMatrix4i;
	typedef CMatrix4<float >		CMatrix4f;
	typedef CMatrix4<double>		CMatrix4d;

	/**
	 * Material interface to assign following appearance attributes to a Geometry Object:
	 *	+ Ambient color
	 *	+ Diffuse color
	 *	+ Specular color
	 *	+ Emission color
	 *	+ Shininess indices
	 *	+ Transparency indices
	 */
	class IMaterial : public CSharedObject
	{
	public:
									IMaterial();
		void						operator = (const IMaterial& other);
		const CVector4f&			GetAmbient();
		void						SetAmbient(const CVector4f &a_Ambient);
		const CVector4f&			GetDiffuse() const;
		void						SetDiffuse(const CVector4f &a_Diffuse);
		const CVector4f&			GetSpecular() const;
		void						SetSpecular(const CVector4f &a_Specular);
		float						GetShine() const;
		void						SetShine(float a_Shine);
		virtual void				Apply() const = 0;
		const CVector4f&			GetEmmision() const;
		void						SetEmmision(const CVector4f a_Emmision);
		float						GetTransparency() const;
		void						SetTransparency(float a_Transparence);

	protected:
		CVector4f					m_Ambient;
		CVector4f					m_Diffuse;
		CVector4f					m_Specular;
		CVector4f					m_Emission;
		float						m_Shine;
		float						m_Transparency;
	};

	/**
	 * BoundingBox interface for Geometry Object
	 */
	class IBoundingBox : public CSharedObject
	{
	public:
									IBoundingBox();
		const  CVector3f &			GetMax()const;
		const  CVector3f &			GetMin()const;
		void						SetMax(const CVector3f & max);
		void						SetMin(const CVector3f & min);
		void						AddPointToBound(const CVector3f & a_Point);
	private:
		CVector3f					m_Max;
		CVector3f					m_Min;
	
	};

	/**
	 * GeometryBaseObject interface to represent any shape in VirtualWorld, which can be
	 * cube, box, sphere, UT-pot, NURBS surfaces, etc.. Or, model loading from files like
	 * .3ds, .obj, .3dxml, .dae, etc.
	 */
	class IGeometryBaseObject : public CSharedObject
	{
	public:
		static const int			GEOMETRY_DRAW_SOLID = 10;
		static const int			GEOMETRY_DRAW_WIRE = 20;
		static const int			GEOMETRY_NORMAL_VERTEX = 30;
		static const int			GEOMETRY_NORMAL_FACET = 40;

									IGeometryBaseObject();
		virtual						~IGeometryBaseObject();
		virtual void				Draw() = 0;
		IBoundingBox*				GetBoundingBox();
		void						SetDrawMode(int a_DrawMode);
		int							GetDrawMode() const;
		void						SetMaterial(IMaterial* a_Material);
		IMaterial*					GetMaterial() const;
		void						SetNormalMode(int a_NormalMode);
		int							GetNormalMode() const;

	protected:
		virtual void				UpdateBoundingBox();

		int							m_DrawMode;
		IMaterial*					m_Material;
		IBoundingBox*				m_BoundingBox;
		int							m_NormalMode;
		bool						m_NeedRedraw;
	};

	/**
	 * GeometryModelObject interface to load and create geometry object from model file
	 */
	class IGeometryModelObject : public IGeometryBaseObject
	{
	public:
		virtual bool				LoadModel(const CString& a_FileName) = 0;				
	};

	/**
	 * GeometryCubeObject interface to create a cube object
	 */
	class IGeometryCubeObject : public IGeometryBaseObject
	{
	public:
									IGeometryCubeObject();
		void						SetRadius(float r);
		float						GetRadius() const;

	protected:
		float						m_Radius;
	};

	/**
	 * GeometrySphereObject interface to create a sphere object
	 */
	class IGeometrySphereObject : public IGeometryBaseObject
	{
	public:
									IGeometrySphereObject();
		void						SetRadius(float r);
		float						GetRadius() const;
		void						SetSlices(int n);
		int							GetSlices() const;
		void						SetStacks(int n);
		int							GetStacks()	const;

	protected:
		float						m_Radius;
		int							m_Slices;
		int							m_Stacks;
	};

	/**
	 * GeometryCylinderObject interface to create a sphere object
	 */
	class IGeometryCylinderObject : public IGeometryBaseObject
	{
	public:
									IGeometryCylinderObject();
		void						SetBaseRadius(float r);
		float						GetBaseRadius() const;
		void						SetTopRadius(float r);
		float						GetTopRadius() const;
		void						SetHeight(float r);
		float						GetHeight() const;
		void						SetSlices(int n);
		int							GetSlices() const;
		void						SetStacks(int n);
		int							GetStacks()	const;

	protected:
		float						m_BaseRadius;
		float						m_TopRadius;
		float						m_Height;
		int							m_Slices;
		int							m_Stacks;
	};

	/**
	 * SceneBaseNode interface as the basic unit of scene graph.
	 * Generally can be divided to GeometryNode which owns a GeometryObject to draw,
	 * and GroupNode which acts as a container to combine GeometryNode(s) or other Group
	 * Node(s)
	 */
	class ISceneBaseNode : public CSharedObject
	{
	public:
		static const int			SCENE_BASE_NODE	= 0;
		static const int			SCENE_CAMERA_NODE = 10;
		static const int			SCENE_LIGHT_NODE = 20;
		static const int			SCENE_GEOMETRY_NODE	= 30;
		static const int			SCENE_GROUP_NODE = 40;

									ISceneBaseNode();
		const CString&				GetName() const;
		void						SetName(const CString& a_Name);
		ISceneBaseNode*				GetParent() const;
		void						SetParent(ISceneBaseNode* a_Parent);
		int							GetNodeType() const ;
		CString						GetNodeTypeString() const;
		bool						GetVisibility() const;
		void						SetVisibility(bool a_Visibility);
		const CMatrix4f&			GetLocalMatrix() const;
		const CMatrix4f&			GetWorldMatrix();
		void						Translate(const CVector3f& t);
		void						Rotate(float angle, const CVector3f& axis);
		void						Scale(const CVector3f& axis);
		void						GotoLocalOrigin();
		void						GotoWorldOrigin();

		virtual void				Draw() = 0;
		virtual void				Update(){}
	
	protected:
		void						UpdateWorldMatrix();
		CString						m_Name;
		ISceneBaseNode*				m_Parent;
		int							m_NodeType;
		bool						m_Visibility;
		CMatrix4f					m_LocalMatrix;
		CMatrix4f					m_WorldMatrix;
	};

	/**
	 * SceneGroupNode interface. Combine other scene node into a group.
	 */
	class ISceneGroupNode : public ISceneBaseNode
	{
	public:
		typedef std::map<CString, ISceneBaseNode*> NodeTable;
									ISceneGroupNode();
		void						AddChild(ISceneBaseNode* a_Child);
		ISceneBaseNode*				GetChild(const CString& a_Name) const;
		const NodeTable&			GetChildren() const;
		void						RemoveChild(ISceneBaseNode* a_Child);
		void						RemoveChild(const CString& a_Name);

	protected:
		NodeTable m_Children;
	};

	/**
	 * SceneCameraNode interface serves as camera in scene graph
	 * Since camera a SceneNode, affine transformation like translate/rotate/scale is also available.
	 * Position, ForwardVector and UpVector are initialized by (0, 0, 0), (0, 0, -1), (0, 1, 0)
	 * And can be calculated from WorldTransformation matrix 
	 * http://www.euclideanspace.com/maths/geometry/affine/matrix4x4/index.htm
	 * http://en.wikipedia.org/wiki/Camera_resectioning
	 * http://math.stackexchange.com/questions/82602/how-to-find-camera-position-and-rotation-from-a-4x4-matrix
	 *
	 * Note: All the operations to manipulate camera are applied to local transformation matrix.
	 *		 Like Translate/Rotate derived from ISceneBaseNode, and LookAt
	 */
	class ISceneCameraNode : public ISceneBaseNode
	{
	public:
									ISceneCameraNode();
		float						GetFovy() const;
		void						SetFovy(float a_Fovy);
		float						GetZNear() const;
		void						SetZNear(float a_ZNear);
		float						GetZFar() const;
		void						SetZFar(float a_ZFar);
		const RECT&					GetRect() const;
		void						SetRect(const RECT& a_Rect);
		void						LookAt(const CVector3f& a_Position, const CVector3f& a_FocusPoint, const CVector3f& a_UpVector);
		virtual void				UpdateViewPort() = 0;
		virtual void				Apply() = 0;
		void						Scale(const CVector3f& axis);

	protected:
		float						m_Fovy;
		float						m_ZNear;
		float						m_ZFar;
		RECT						m_Rect;
	};

	/**
	 * SceneLightNode interface 
	 */
	class ISceneLightNode : public ISceneBaseNode
	{
	public:
									ISceneLightNode();
		int							GetID() const;
		const CVector4f&			GetAmbient();
		void						SetAmbient(const CVector4f &a_Ambient);
		const CVector4f&			GetDiffuse() const;
		void						SetDiffuse(const CVector4f &a_Diffuse);
		const CVector4f&			GetSpecular() const;
		void						SetSpecular(const CVector4f &a_Specular);
		const CVector4f&			GetPosition() const;
		void						SetPosition(const CVector4f &a_Position);
		const CVector3f&			GetSpotDirection() const;
		void						SetSpotDirection(const CVector3f &a_SpotDirection);
		float						GetSpotExponent() const;
		void						SetSpotExponent(float a_SpotExponent);
		float						GetSpotCutoff() const;
		void						SetSpotCutoff(float a_SpotCutoff);
		const CVector3f&			GetAttenuation() const;
		void						SetAttenuation(const CVector3f& a_Attenuation);

	protected:
		int							m_ID;
		CVector4f					m_Ambient;
		CVector4f					m_Diffuse;
		CVector4f					m_Specular;
		CVector4f					m_Position;
		CVector3f					m_SpotDirection;
		float						m_SpotExponent;
		float						m_SpotCutoff;
		CVector3f					m_Attenuation;
	};

	/**
	 * SceneGeometryNode interface contains a GeometryObject to draw
	 */
	class ISceneGeometryNode : public ISceneBaseNode
	{
	public:
									ISceneGeometryNode();
		virtual void				SetGeometryObject(IGeometryBaseObject* a_Object) = 0;
		virtual IGeometryBaseObject* GetGeometryObject() const = 0;
	};

	/**
	 * GUIEventHandler interface to reflect Win32 event like keyboard and mouse
	 */
	class IGUIEventHandler
	{
	public:
		virtual void				OnMove(const CPoint& ptPos) = 0;
		virtual	void				OnSize(const CSize& size) = 0;
		virtual void				OnLButtonDown(unsigned nFlags, const CPoint& point) = 0;
		virtual void				OnLButtonUp(unsigned nFlags, const CPoint& point) = 0;
		virtual void				OnLButtonDblClk(unsigned nFlags, const CPoint& point) = 0;
		virtual void				OnRButtonDown(unsigned nFlags, const CPoint& point) = 0;
		virtual void				OnRButtonUp(unsigned nFlags, const CPoint& point) = 0;
		virtual void				OnRButtonDblClk(unsigned nFlags, const CPoint& point) = 0;
		virtual void				OnMouseMove(unsigned nFlags, const CPoint& point) = 0;
		virtual BOOL				OnMouseWheel(unsigned nFlags, short zDelta, const CPoint& pt) = 0;
		virtual void				OnKeyDown(unsigned nChar, unsigned nRepCnt, unsigned nFlags) = 0;
		virtual void				OnKeyUp(unsigned nChar, unsigned nRepCnt, unsigned nFlags) = 0;
	};

	/**
	 * Window32 interface manages win32 style window which contains a root scene node.
	 */
	class IWindow32
	{
	public:
									IWindow32();
		virtual						~IWindow32();
		virtual HWND				CreateWin (HWND hWndParent, 
										_U_RECT rect = NULL, 
										LPCTSTR szWindowName = NULL,
										DWORD dwStyle = 0,
										DWORD dwExStyle = 0,
										_U_MENUorID MenuOrID = 0U,
										LPVOID lpCreateParam = NULL) = 0;
		virtual HWND				GetHwnd() const = 0;
		virtual BOOL				OnIdle() = 0;
		virtual BOOL				RedrawWin(CONST RECT *lprcUpdate = NULL, 
										HRGN hrgnUpdate = NULL, 
										UINT flags = RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE) = 0;
		virtual BOOL				PreTranslateMessage(MSG* pMsg) = 0;
		ISceneGroupNode*			GetRootSGNode() const;
		void						SetRootSGNode(ISceneGroupNode* a_RootSGNode);
		ISceneCameraNode*			GetActiveCameraNode() const;
		void						SetActiveCameraNode(ISceneCameraNode* a_CameraNode);
		IGUIEventHandler*			GetGUIEventHandler() const;
		void						SetGUIEventHandler(IGUIEventHandler* a_GUIEventHandler);
	
	protected:
		ISceneGroupNode*			m_RootSGNode;
		ISceneCameraNode*			m_ActiveCameraNode;
		IGUIEventHandler*			m_GUIEventHandler;
	};


	/**
	 * class: CFactory
	 * function: Create instance for interfaces
	 */
	class VIRTUALWORLD_API CFactory : public CSingleton<CFactory>
	{
	public:
		IWindow32*					CreateWindow32();
		ISceneGroupNode*			CreateSceneGroupNode();
		ISceneGeometryNode*			CreateSceneGeometryNode();
		ISceneCameraNode*			CreateSceneCameraNode();
		ISceneLightNode*			CreateSceneLightNode();
		IGeometryCubeObject*		CreateGeometryBoxObject();
		IGeometrySphereObject*		CreateGeometrySphereObject();
		IGeometryCylinderObject*	CreateGeometryCylinderObject();
		IGeometryModelObject*		CreateGeometryModelObject(const CString& a_FileType);
		IMaterial*					CreateMaterial();
		
	private:
		friend class CSingleton<CFactory>;
	};

	class VIRTUALWORLD_API CUtility
	{
	public:
		static char* CStringToPChar(const CString& str);
		static CString GetFileSuffix(const CString& str);
		static CString GetFileName(const CString& str);
		static CString PathToUnixStyle(const CString& str);
	};
}

#include "VirtualWorld.inl"