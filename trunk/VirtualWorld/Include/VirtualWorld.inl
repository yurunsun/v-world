namespace VirtualWorld
{
	template<class T>
	inline T* CSingleton<T>::GetInstance()
	{
		static T Instance;
		return &Instance;
	}
	//-----------------------------------------------------------------------//
	inline unsigned long CSharedObject::AddRef()
	{ 
		return (++m_Ref); 
	}
	//-----------------------------------------------------------------------//
	inline unsigned long CSharedObject::Release()
	{
		--m_Ref;
		if (m_Ref == 0) {
			delete this;
		}
		return m_Ref;
	}
	//-----------------------------------------------------------------------//
	template<class T>
	inline CVector4<T>::CVector4(T a_X = 0, T a_Y = 0, T a_Z = 0, T a_W = 1) 
		: x(a_X), y(a_Y), z(a_Z),w(a_W)
	{}
	//-----------------------------------------------------------------------//
	template<class T>
	inline CVector4<T>::CVector4(T a_XYZW) 
		: x(a_XYZW), y(a_XYZW), z(a_XYZW), w(a_XYZW) 
	{}
	//-----------------------------------------------------------------------//
	template<class T>
	inline CVector4<T>::CVector4(const CVector4<T> &a_C) 
		: x(a_C.x), y(a_C.y), z(a_C.z), w(a_C.w)
	{}
	//-----------------------------------------------------------------------//
	template<class T>
	inline CVector4<T>::operator T *() 
	{
		return m_Values;
	}
	//-----------------------------------------------------------------------//
	template<class T>
	inline CVector4<T>::operator const T* () const 
	{ 
		return m_Values;
	}
	//-----------------------------------------------------------------------//
	template<class T>
	inline const T CVector4<T>::operator[](unsigned int a_Index) const 
	{ 
		return ((T*)&x)[a_Index]; 
	}

	//-----------------------------------------------------------------------//
	template<class T>
	inline T& CVector4<T>::operator[](unsigned int a_Index)
	{ 
		return ((T*)&x)[a_Index]; 
	}
	//-----------------------------------------------------------------------//
	template<class T>
	inline CVector4<T>& CVector4<T>::operator = (const CVector4<T> &a_Source)
	{
		x = a_Source.x;
		y = a_Source.y;
		z = a_Source.z;
		w = a_Source.w;
		return *this;
	}
	//-----------------------------------------------------------------------//
	template<class T>
	inline CVector4<T> CVector4<T>::operator + (const CVector4<T> &a_Right)
	{
		return CVector4<T>(a_Right.x + x, a_Right.y + y, a_Right.z + z, a_Right.w + w );
	}
	//-----------------------------------------------------------------------//
	template<class T>
	inline CVector4<T> CVector4<T>::operator - (const CVector4<T>  &a_Right)
	{
		return CVector4<T>(-a_Right.x + x, -a_Right.y + y, -a_Right.z + z, -a_Right.w + w );
	}
	//-----------------------------------------------------------------------//
	template<class T>
	inline CVector4<T> CVector4<T>::operator * (const T a_Scale)
	{
		return CVector4<T>(x*a_Scale, y*a_Scale, z*a_Scale, w*a_Scale);
	}
	//-----------------------------------------------------------------------//
	template<class T>
	inline CVector4<T> CVector4<T>::operator / (const T a_Scale)
	{
		return a_Scale ? CVector4<T>(x/a_Scale, y/a_Scale, z/a_Scale, w/a_Scale) : CVector4<T>(0, 0, 0, 0);
	}
	//-----------------------------------------------------------------------//
	template<class T>
	inline CVector4<T>& CVector4<T>::operator += (const CVector4<T> &a_Right)
	{
		x += a_Right.x;
		y += a_Right.y;
		z += a_Right.z;
		w += a_Right.w;
		return *this;
	}
	//-----------------------------------------------------------------------//
	template<class T>
	inline CVector4<T> CVector4<T>::operator -= (const CVector4<T>  &a_Right)
	{
		x -= a_Right.x;
		y -= a_Right.y;
		z -= a_Right.z;
		w -= a_Right.w;
		return *this;
	}
	//-----------------------------------------------------------------------//
	template<class T>
	inline CVector4<T> CVector4<T>::operator *= (const T a_Scale)
	{
		x *= a_Scale;
		y *= a_Scale;
		z *= a_Scale;
		w *= a_Scale;
		return *this;
	}
	//-----------------------------------------------------------------------//
	template<class T>
	inline CVector4<T> CVector4<T>::operator /= (const T a_Scale)
	{
		if(a_Scale) {
			x /= a_Scale;
			y /= a_Scale;
			z /= a_Scale;
			w /= a_Scale;
		}
		return *this;
	}
	//-----------------------------------------------------------------------//
	template<class T>
	inline bool CVector4<T>::operator == (const CVector4<T> &a_Right)
	{
		return (x == a_Right.x &&
			y == a_Right.y &&
			z == a_Right.z &&
			w == a_Right.w);
	}
	//-----------------------------------------------------------------------//
	template<class T>
	inline bool CVector4<T>::operator != (const CVector4<T> &a_Right)
	{
		return !(x == a_Right.x &&
			y == a_Right.y &&
			z == a_Right.z &&
			w == a_Right.w);
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CVector3<T>::CVector3(T a_x, T a_y, T a_z)
		: x (a_x), y (a_y), z (a_z)
	{}
	//-----------------------------------------------------------------------//	
	template <class T>
	inline CVector3<T>::CVector3(T a_xyz)
		: x (a_xyz), y (a_xyz), z (a_xyz)
	{}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CVector3<T>::CVector3(const CVector3<T> &a_Source)
		: x (a_Source.x), y (a_Source.y), z (a_Source.z)
	{}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CVector3<T>::operator const T*() const
	{
		return m_Values;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CVector3<T>::operator T*()
	{
		return m_Values;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CVector3<T> & CVector3<T>::operator=( const CVector3<T> &a_Right )
	{
		x = a_Right.x;
		y = a_Right.y;
		z = a_Right.z;
		return *this;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CVector3<T> CVector3<T>::operator+( const CVector3<T> &a_Right )const
	{
		return CVector3(a_Right.x + x, a_Right.y + y, a_Right.z + z);
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CVector3<T> CVector3<T>::operator - ( const CVector3<T> &a_Right )const
	{
		return CVector3<T>(-a_Right.x + x, -a_Right.y + y, -a_Right.z + z);
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CVector3<T> CVector3<T>::operator *( const T a_Scale )const
	{
		return CVector3<T>(x*a_Scale, y*a_Scale, z*a_Scale);
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CVector3<T> CVector3<T>::operator/( const T a_Scale )const
	{
		return (a_Scale ? CVector3<T>(x/a_Scale, y/a_Scale, z/a_Scale): CVector3<T>(0, 0, 0));
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CVector3<T> & CVector3<T>::operator+=( const CVector3<T> &a_Right )
	{
		x += a_Right.x;
		y += a_Right.y;
		z += a_Right.z;
		return *this;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CVector3<T> & CVector3<T>::operator+=( const T a_xyz )
	{
		x += a_xyz;
		y += a_xyz;
		z += a_xyz;
		return *this;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CVector3<T> & CVector3<T>::operator-=( const CVector3<T> &a_Right )
	{
		x -= a_Right.x;
		y -= a_Right.y;
		z -= a_Right.z;
		return *this;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CVector3<T> & CVector3<T>::operator-=( const T a_xyz )
	{
		x -= a_xyz;
		y -= a_xyz;
		z -= a_xyz;
		return *this;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CVector3<T> & CVector3<T>::operator*=( const T a_Scale )
	{
		x *= a_Scale;
		y *= a_Scale;
		z *= a_Scale;
		return *this;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CVector3<T> & CVector3<T>::operator/=( const T a_Scale )
	{
		if(a_Scale) 
		{
			x/=a_Scale;
			y/=a_Scale;
			z/=a_Scale;
		}
		return *this;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline bool CVector3<T>::operator==( const CVector3 &a_Right )
	{
		return (x == a_Right.x &&
			y == a_Right.y &&
			z == a_Right.z);
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline bool CVector3<T>::operator!=( const CVector3 &a_Right )
	{
		return !(x == a_Right.x &&
			y == a_Right.y &&
			z == a_Right.z);
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline const T CVector3<T>::operator[]( unsigned i ) const
	{
		return ((T*)&x)[i];
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline T & CVector3<T>::operator[]( unsigned i )
	{
		return ((T*)&x)[i];
	}
	//-----------------------------------------------------------------------//
	template <class T>
	void VirtualWorld::CVector3<T>::Set(const T x, const T y, const T z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline void	CVector3<T>::Zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CVector3<T>& CVector3<T>::Normalize()
	{
		T length  = Length();
		if(!length) {
			this->Zero();
			return *this;
		}
		x /= length;
		y /= length;
		z /= length;
		return *this;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline const T CVector3<T>::LengthSquared() const
	{
		return  x*x + y*y + z*z;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline const T CVector3<T>::Length() const
	{
		return std::sqrtf(x*x + y*y + z*z);
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline const T VirtualWorld::CVector3<T>::DotProduct(const CVector3<T>& t) const
	{
		return x*t.x + y*t.y + z*t.z;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CVector3<T>& VirtualWorld::CVector3<T>::CrossProduct(const CVector3<T>& t1, const CVector3<T>& t2)
	{
		Set(t1.y * t2.z - t1.z * t2.y,
			t2.x * t1.z - t2.z * t1.x,
			t1.x * t2.y - t1.y * t2.x);
		return *this;
	}
	//-----------------------------------------------------------------------//
	// Actually this is coordinate transformation matrix calculation:
	//	I(O, (x, y, z)) -> I'(O', (x', y', z'))
	// 
	// Algorithm can reference to any analytic geometry textbook, or the following URLs:
	// http://home.scarlet.be/~ping1339/coortf.htm
	// http://en.wikipedia.org/wiki/Cartesian_coordinate_system
	template <class T>
	inline CMatrix4<T>& VirtualWorld::CMatrix4<T>::LookAt(const CVector3<T>& a_Position, const CVector3<T>& a_FocusPoint, const CVector3<T>& a_UpVector)
	{
		CVector3<T>* xaxis = (CVector3<T> *) m_Values;
		CVector3<T>* up    = (CVector3<T> *)(m_Values + 4);
		CVector3<T>* at    = (CVector3<T> *)(m_Values + 8);

		*at  = a_FocusPoint;
		*at -= a_Position;
		at->Normalize();

		
		xaxis->CrossProduct(*at, a_UpVector);	// X axis of I' in I
		xaxis->Normalize();
		up->CrossProduct(*xaxis, *at);			// Y axis of I' in I
		*at *= -1.f;							// Z axis of I' in I

		m_Values[3]  = 0.0f;
		m_Values[7]  = 0.0f;
		m_Values[11] = 0.0f;

		m_Values[12] = a_Position.x;
		m_Values[13] = a_Position.y; 
		m_Values[14] = a_Position.z;
		m_Values[15] = 1.0f;
		return *this;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CVector3f VirtualWorld::CMatrix4<T>::RightVector() const
	{
		return CVector3f(this->m_Values[0],	this->m_Values[1],	this->m_Values[2]);
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CVector3f VirtualWorld::CMatrix4<T>::UpVector() const
	{
		return CVector3f(this->m_Values[4],	this->m_Values[5],	this->m_Values[6]);
	}
	//-----------------------------------------------------------------------//
	template <class T>
	CVector3f VirtualWorld::CMatrix4<T>::ForwardVector() const
	{
		return CVector3f(this->m_Values[8],	this->m_Values[9],	this->m_Values[10]);
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CVector3f VirtualWorld::CMatrix4<T>::TranslationVector() const
	{
		return CVector3f(this->m_Values[12],	this->m_Values[13],	this->m_Values[14]);
	}
	//-----------------------------------------------------------------------//
	inline IMaterial::IMaterial()
	{
		this->m_Ambient		= CVector4f(0.2f,0.2f,0.2f,1.0f);
		this->m_Diffuse		= CVector4f(0.3f,0.8f,0.3f,1.0f);
		this->m_Specular	= CVector4f(0.0f,0.0f,0.0f,1.0f);
		this->m_Emission	= CVector4f(0.0f,0.0f,0.0f,1.0f);
		this->m_Shine		= 0.0f;
		this->m_Transparency= 1.0f;
	}
	//-----------------------------------------------------------------------//
	inline void IMaterial::operator =(const IMaterial& other)
	{
		this->m_Ambient		= other.m_Ambient;
		this->m_Diffuse		= other.m_Diffuse;
		this->m_Specular	= other.m_Specular;
		this->m_Emission	= other.m_Emission;
		this->m_Shine		= other.m_Shine;
		this->m_Transparency= other.m_Transparency;
	}
	//-----------------------------------------------------------------------//
	inline const CVector4f& IMaterial::GetAmbient()
	{ 
		return m_Ambient; 
	}
	//-----------------------------------------------------------------------//
	inline void	IMaterial::SetAmbient(const CVector4f &a_Ambient) 
	{ 
		m_Ambient = a_Ambient; 
	}
	//-----------------------------------------------------------------------//
	inline const CVector4f&	IMaterial::GetDiffuse() const 
	{
		return m_Diffuse; 
	}
	//-----------------------------------------------------------------------//
	inline void	IMaterial::SetDiffuse(const CVector4f &a_Diffuse) 
	{ 
		m_Diffuse = a_Diffuse; 
	}
	//-----------------------------------------------------------------------//
	inline const CVector4f&	IMaterial::GetSpecular() const
	{ 
		return m_Specular; 
	}
	//-----------------------------------------------------------------------//
	inline void	IMaterial::SetSpecular(const CVector4f &a_Specular) 
	{ 
		m_Specular = a_Specular; 
	}
	//-----------------------------------------------------------------------//
	inline float IMaterial::GetShine() const 
	{ 
		return m_Shine; 
	}
	//-----------------------------------------------------------------------//
	inline void	IMaterial::SetShine(float a_Shine) 
	{
		m_Shine = a_Shine; 
	}
	//-----------------------------------------------------------------------//
	inline const CVector4f&	IMaterial::GetEmmision() const 
	{
		return m_Emission;
	}
	inline void	IMaterial::SetEmmision(const CVector4f a_Emmision) 
	{ 
		m_Emission = a_Emmision; 
	}
	//-----------------------------------------------------------------------//
	inline float IMaterial::GetTransparency() const 
	{ 
		return m_Transparency; 
	}
	//-----------------------------------------------------------------------//
	inline void	IMaterial::SetTransparency(float a_Transparence) 
	{ 
		m_Transparency = a_Transparence; 
		m_Ambient.a *= m_Transparency;
		m_Diffuse.a *= m_Transparency;
		m_Specular.a *= m_Transparency;
		m_Emission.a *= m_Transparency;
	}
	//-----------------------------------------------------------------------//
	inline IBoundingBox::IBoundingBox()
		: m_Max(0.0f, 0.0f, 0.0f)
		, m_Min(0.0f, 0.0f, 0.0f)
	{
	}
	//-----------------------------------------------------------------------//
	inline const CVector3f & IBoundingBox::GetMax() const
	{
		return m_Max;
	}
	//-----------------------------------------------------------------------//
	inline const CVector3f & IBoundingBox::GetMin() const
	{
		return m_Min;
	}
	//-----------------------------------------------------------------------//
	inline void IBoundingBox::SetMax(const CVector3f& max)
	{
		m_Max = max;
	}
	//-----------------------------------------------------------------------//
	inline void IBoundingBox::SetMin(const CVector3f& min)
	{
		m_Min = min;
	}
	//-----------------------------------------------------------------------//
	inline void IBoundingBox::AddPointToBound(const CVector3f& a_Point)
	{
		m_Min.x = min(a_Point.x, m_Min.x);
		m_Max.x = max(a_Point.x, m_Max.x);
		m_Min.y = min(a_Point.y, m_Min.y);
		m_Max.y = max(a_Point.y, m_Max.y);
		m_Min.z = min(a_Point.z, m_Min.z);
		m_Max.z = max(a_Point.z, m_Max.z);
	}
	//-----------------------------------------------------------------------//
	inline IGeometryBaseObject::IGeometryBaseObject()
		: m_DrawMode(GEOMETRY_DRAW_WIRE) 
		, m_Material(NULL)
		, m_BoundingBox(NULL)
		, m_NormalMode(GEOMETRY_NORMAL_FACET)
		, m_NeedRedraw(true)
	{}
	//-----------------------------------------------------------------------//
	inline IGeometryBaseObject::~IGeometryBaseObject()
	{
		if (m_Material != NULL) {
			m_Material->Release();
		}
		if (m_BoundingBox != NULL) {
			m_BoundingBox->Release();
		}
	}
	inline IBoundingBox* IGeometryBaseObject::GetBoundingBox()
	{
		if (m_BoundingBox == NULL) {
			m_BoundingBox = new IBoundingBox;
			this->UpdateBoundingBox();
		}
		return m_BoundingBox;
	}

	//-----------------------------------------------------------------------//
	inline void	IGeometryBaseObject::SetDrawMode(int a_DrawMode) 
	{ 
		m_DrawMode = a_DrawMode; 
		m_NeedRedraw = true;
	}
	//-----------------------------------------------------------------------//
	inline int IGeometryBaseObject::GetDrawMode() const 
	{ 
		return m_DrawMode; 
	}
	//-----------------------------------------------------------------------//
	inline void	IGeometryBaseObject::SetMaterial(IMaterial* a_Material)
	{
		if (m_Material != NULL) {
			m_Material->Release();
		}
		m_Material = a_Material;
		if (m_Material != NULL) {
			m_Material->AddRef();
		}
		m_NeedRedraw = true;
	}
	//-----------------------------------------------------------------------//
	inline IMaterial* IGeometryBaseObject::GetMaterial() const 
	{ 
		return m_Material; 
	}
	//-----------------------------------------------------------------------//
	inline void	IGeometryBaseObject::SetNormalMode(int a_NormalMode) 
	{ 
		m_NormalMode = a_NormalMode; 
		m_NeedRedraw = true;
	}
	//-----------------------------------------------------------------------//
	inline int IGeometryBaseObject::GetNormalMode() const 
	{ 
		return m_NormalMode; 
	}
	//-----------------------------------------------------------------------//
	inline void IGeometryBaseObject::UpdateBoundingBox()
	{
		// Leave for derived class to implement
	}
	//-----------------------------------------------------------------------//
	inline IGeometryCubeObject::IGeometryCubeObject() 
		: m_Radius(1.0f)
	{
	}
	//-----------------------------------------------------------------------//
	inline void	IGeometryCubeObject::SetRadius(float r) 
	{ 
		if (r > 0.1) {
			m_Radius = r;
			m_NeedRedraw = true;
		}
	}
	//-----------------------------------------------------------------------//
	inline float IGeometryCubeObject::GetRadius() const 
	{ 
		return m_Radius; 
	}

	//-----------------------------------------------------------------------//
	inline IGeometrySphereObject::IGeometrySphereObject() 
		: m_Radius(1.0f)
		, m_Slices(12)
		, m_Stacks(12)
	{}

	//-----------------------------------------------------------------------//
	inline void	IGeometrySphereObject::SetRadius(float r) 
	{ 
		if(r > 0.1) {
			m_Radius = r; 
			m_NeedRedraw = true;
		}
	}
	//-----------------------------------------------------------------------//
	inline float IGeometrySphereObject::GetRadius() const 
	{ 
		return m_Radius; 
	}
	//-----------------------------------------------------------------------//
	inline void	IGeometrySphereObject::SetSlices(int n)  
	{ 
		if( n > 1) {
			m_Slices = n; 
			m_NeedRedraw = true;
		}
	}
	//-----------------------------------------------------------------------//
	inline int IGeometrySphereObject::GetSlices() const 
	{ 
		return m_Slices; 
	}
	//-----------------------------------------------------------------------//
	inline void IGeometrySphereObject::SetStacks(int n)  
	{ 
		if(n > 1) {
			m_Stacks = n; 
			m_NeedRedraw = true;
		}
	}
	//-----------------------------------------------------------------------//
	inline int IGeometrySphereObject::GetStacks()	const 
	{ 
		return m_Stacks; 
	}
	//-----------------------------------------------------------------------//
	inline IGeometryCylinderObject::IGeometryCylinderObject()
		: m_BaseRadius(0.2f)
		, m_TopRadius(0.2f)
		, m_Height(0.4f)
		, m_Slices(12)
		, m_Stacks(12)
	{
	}
	//-----------------------------------------------------------------------//
	inline void	IGeometryCylinderObject::SetBaseRadius(float r)
	{
		if (r > 0.1) {
			m_BaseRadius = r;
			m_NeedRedraw = true;
		}
	}
	//-----------------------------------------------------------------------//
	inline float IGeometryCylinderObject::GetBaseRadius() const
	{
		return m_BaseRadius;
	}
	//-----------------------------------------------------------------------//
	inline void	IGeometryCylinderObject::SetTopRadius(float r)
	{
		if (r > 0.1) {
			m_TopRadius = r;
			m_NeedRedraw = true;
		}
	}
	//-----------------------------------------------------------------------//
	inline float IGeometryCylinderObject::GetTopRadius() const
	{
		return m_TopRadius;
	}
	//-----------------------------------------------------------------------//
	inline void	IGeometryCylinderObject::SetHeight(float r)
	{
		if (r > 0.1) {
			m_Height = r;
			m_NeedRedraw = true;
		}
	}
	//-----------------------------------------------------------------------//
	inline float IGeometryCylinderObject::GetHeight() const
	{
		return m_Height;
	}
	//-----------------------------------------------------------------------//
	inline void	IGeometryCylinderObject::SetSlices(int n)
	{
		if (n > 1) {
			m_Slices = n;
			m_NeedRedraw = true;
		}
	}
	//-----------------------------------------------------------------------//
	inline int IGeometryCylinderObject::GetSlices() const
	{
		return m_Slices;
	}
	//-----------------------------------------------------------------------//
	inline void	IGeometryCylinderObject::SetStacks(int n)
	{
		if (n > 1) {
			m_Stacks = n;
			m_NeedRedraw = true;
		}
	}
	//-----------------------------------------------------------------------//
	inline int IGeometryCylinderObject::GetStacks()	const
	{
		return m_Stacks;
	}

	//-----------------------------------------------------------------------//
	template <class T>
	inline CMatrix4<T>::CMatrix4( T scale /*= 1*/ ) 
		: _11(scale),		_12(0),		_13(0),		_14(0)
		, _21(0),			_22(scale), _23(0),		_24(0)
		, _31(0),			_32(0),		_33(scale),	_34(0)
		, _41(0),			_42(0),		_43(0),		_44(1)
	{
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CMatrix4<T>::CMatrix4(const T* a_Elements)
	{
		memcpy(m_Values, a_Elements, sizeof(T)*16);
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CMatrix4<T>::CMatrix4(const CMatrix4<T> &a_Matrix)
	{
		memcpy(m_Values, a_Matrix.m_Values, sizeof(T)*16);
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CMatrix4<T>::CMatrix4( T m0, T m1, T m2, T m3, T m4, T m5, T m6, T m7, T m8, T m9, T m10, T m11, T m12,T m13, T m14, T m15 )
	{
		m_Values[ 0] =  m0; m_Values[ 1] =  m1; m_Values[ 2] =  m2; m_Values[ 3] =  m3;
		m_Values[ 4] =  m4; m_Values[ 5] =  m5; m_Values[ 6] =  m6; m_Values[ 7] =  m7;
		m_Values[ 8] =  m8; m_Values[ 9] =  m9; m_Values[10] = m10; m_Values[11] = m11;
		m_Values[12] = m12; m_Values[13] = m13; m_Values[14] = m14; m_Values[15] = m15;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CMatrix4<T> CMatrix4<T>::operator * ( const CMatrix4<T> &other ) const
	{
		CMatrix4<T> newMatrix;
		int column = 0;
		for (int i = 0; i < 4; i++) {		// rows
			for (int j = 0; j < 4; j++) {	//each column
				float val = 0;
				for (int k = 0; k < 4; k++) {
					val += m_Matrix[i][k] * other.m_Matrix[k][j];
				}  
				newMatrix.m_Matrix[i][j] = val;
			}
		}
		return newMatrix;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CMatrix4<T> CMatrix4<T>::operator + ( const CMatrix4<T> &mat ) const
	{
		return CMatrix4(m_Values[ 0] + mat.m_Values[ 0], m_Values[ 1] + mat.m_Values[ 1], m_Values[ 2] + mat.m_Values[ 2], m_Values[ 3] + mat.m_Values[ 3],
			m_Values[ 4] + mat.m_Values[ 4], m_Values[ 5] + mat.m_Values[ 5], m_Values[ 6] + mat.m_Values[ 6], m_Values[ 7] + mat.m_Values[ 7],
			m_Values[ 8] + mat.m_Values[ 8], m_Values[ 9] + mat.m_Values[ 9], m_Values[10] + mat.m_Values[10], m_Values[11] + mat.m_Values[11],
			m_Values[12] + mat.m_Values[12], m_Values[13] + mat.m_Values[13], m_Values[14] + mat.m_Values[14], m_Values[15] + mat.m_Values[15]);
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CMatrix4<T> CMatrix4<T>::operator-( const CMatrix4<T> &mat ) const
	{
		return CMatrix4(m_Values[ 0] - mat.m_Values[ 0], m_Values[ 1] - mat.m_Values[ 1], m_Values[ 2] - mat.m_Values[ 2], m_Values[ 3] - mat.m_Values[ 3],
			m_Values[ 4] - mat.m_Values[ 4], m_Values[ 5] - mat.m_Values[ 5], m_Values[ 6] - mat.m_Values[ 6], m_Values[ 7] - mat.m_Values[ 7],
			m_Values[ 8] - mat.m_Values[ 8], m_Values[ 9] - mat.m_Values[ 9], m_Values[10] - mat.m_Values[10], m_Values[11] - mat.m_Values[11],
			m_Values[12] - mat.m_Values[12], m_Values[13] - mat.m_Values[13], m_Values[14] - mat.m_Values[14], m_Values[15] - mat.m_Values[15]);
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CMatrix4<T> & CMatrix4<T>::operator+=( const CMatrix4<T> &mat )
	{
		for(unsigned i = 0; i < 16; i++)
			m_Values[i] += mat.m_Values[i];
		return *this;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CMatrix4<T> & CMatrix4<T>::operator*=( const T f )
	{
		for(unsigned i = 0; i < 16; i++)
			m_Values[i] *= f;
		return *this;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CMatrix4<T> & CMatrix4<T>::operator*=( const CMatrix4<T> &mat )
	{
		Set(m_Values[0]*mat.m_Values[ 0]+m_Values[4]*mat.m_Values[ 1]+m_Values[ 8]*mat.m_Values[ 2]+ m_Values[12]*mat.m_Values[ 3],
			m_Values[1]*mat.m_Values[ 0]+m_Values[5]*mat.m_Values[ 1]+m_Values[ 9]*mat.m_Values[ 2]+ m_Values[13]*mat.m_Values[ 3],
			m_Values[2]*mat.m_Values[ 0]+m_Values[6]*mat.m_Values[ 1]+m_Values[10]*mat.m_Values[ 2]+ m_Values[14]*mat.m_Values[ 3],
			m_Values[3]*mat.m_Values[ 0]+m_Values[7]*mat.m_Values[ 1]+m_Values[11]*mat.m_Values[ 2]+ m_Values[15]*mat.m_Values[ 3],
			m_Values[0]*mat.m_Values[ 4]+m_Values[4]*mat.m_Values[ 5]+m_Values[ 8]*mat.m_Values[ 6]+ m_Values[12]*mat.m_Values[ 7],
			m_Values[1]*mat.m_Values[ 4]+m_Values[5]*mat.m_Values[ 5]+m_Values[ 9]*mat.m_Values[ 6]+ m_Values[13]*mat.m_Values[ 7],
			m_Values[2]*mat.m_Values[ 4]+m_Values[6]*mat.m_Values[ 5]+m_Values[10]*mat.m_Values[ 6]+ m_Values[14]*mat.m_Values[ 7],
			m_Values[3]*mat.m_Values[ 4]+m_Values[7]*mat.m_Values[ 5]+m_Values[11]*mat.m_Values[ 6]+ m_Values[15]*mat.m_Values[ 7],
			m_Values[0]*mat.m_Values[ 8]+m_Values[4]*mat.m_Values[ 9]+m_Values[ 8]*mat.m_Values[10]+ m_Values[12]*mat.m_Values[11],
			m_Values[1]*mat.m_Values[ 8]+m_Values[5]*mat.m_Values[ 9]+m_Values[ 9]*mat.m_Values[10]+ m_Values[13]*mat.m_Values[11],
			m_Values[2]*mat.m_Values[ 8]+m_Values[6]*mat.m_Values[ 9]+m_Values[10]*mat.m_Values[10]+ m_Values[14]*mat.m_Values[11],
			m_Values[3]*mat.m_Values[ 8]+m_Values[7]*mat.m_Values[ 9]+m_Values[11]*mat.m_Values[10]+ m_Values[15]*mat.m_Values[11],
			m_Values[0]*mat.m_Values[12]+m_Values[4]*mat.m_Values[13]+m_Values[ 8]*mat.m_Values[14]+ m_Values[12]*mat.m_Values[15],
			m_Values[1]*mat.m_Values[12]+m_Values[5]*mat.m_Values[13]+m_Values[ 9]*mat.m_Values[14]+ m_Values[13]*mat.m_Values[15],
			m_Values[2]*mat.m_Values[12]+m_Values[6]*mat.m_Values[13]+m_Values[10]*mat.m_Values[14]+ m_Values[14]*mat.m_Values[15],
			m_Values[3]*mat.m_Values[12]+m_Values[7]*mat.m_Values[13]+m_Values[11]*mat.m_Values[14]+ m_Values[15]*mat.m_Values[15]);
		return *this;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CMatrix4<T> & CMatrix4<T>::operator-=( const CMatrix4<T> &mat )
	{
		for(unsigned i = 0; i < 16; i++)
			m_Values[i] -= mat.m_Values[i];
		return *this;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline bool CMatrix4<T>::operator==( const CMatrix4<T> &mat )
	{
		return memcmp(m_Values, mat.m_Values, sizeof(T)*16) == 0;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline bool CMatrix4<T>::operator!=( const CMatrix4<T> &mat )
	{
		return memcmp(m_Values, mat.m_Values, sizeof(T)*16) != 0;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CMatrix4<T>& CMatrix4<T>::operator=( const CMatrix4<T> &mat )
	{
		memcpy(m_Values,mat.m_Values, sizeof(T)*16);
		return *this;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CMatrix4<T>::operator const T*() const
	{
		return this->m_Values;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline CMatrix4<T>::operator T*() const
	{
		return this->m_Values;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline void CMatrix4<T>::Set( const T* elements )
	{
		memcpy(m_Values, elements, sizeof(T)*16);
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline void CMatrix4<T>::Set( T m0, T m1, T m2, T m3, T m4, T m5, T m6, T m7, T m8, T m9, T m10, T m11, T m12, T m13, T m14, T m15 )
	{
		m_Values[ 0] =  m0; m_Values[ 1] =  m1; m_Values[ 2] =  m2; m_Values[ 3] =  m3;
		m_Values[ 4] =  m4; m_Values[ 5] =  m5; m_Values[ 6] =  m6; m_Values[ 7] =  m7;
		m_Values[ 8] =  m8; m_Values[ 9] =  m9; m_Values[10] = m10; m_Values[11] = m11;
		m_Values[12] = m12; m_Values[13] = m13; m_Values[14] = m14; m_Values[15] = m15;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline void CMatrix4<T>::Identity()
	{
		m_Values[ 0] = 1; m_Values[ 1] = 0; m_Values[ 2] = 0; m_Values[ 3] = 0;
		m_Values[ 4] = 0; m_Values[ 5] = 1; m_Values[ 6] = 0; m_Values[ 7] = 0;
		m_Values[ 8] = 0; m_Values[ 9] = 0; m_Values[10] = 1; m_Values[11] = 0;
		m_Values[12] = 0; m_Values[13] = 0; m_Values[14] = 0; m_Values[15] = 1;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	inline void CMatrix4<T>::Set( const CMatrix4<T> &matrix )
	{
		memcpy(m_Values, matrix.m_Values, sizeof(T) * 16);
	}
	//-----------------------------------------------------------------------//
	// http://en.wikipedia.org/wiki/Rotation_(geometry)
	template <class T>
	inline void CMatrix4<T>::IdentityRotate(T angle, const CVector3<T>& axis)
	{
		float sinAngle = std::sin(angle), cosAngle = std::cos(angle), oneMinusCosAngle = 1.0f - cosAngle;
		CVector3<T> a = axis;
		a.Normalize();
		Identity();

		m_Values[ 0] = (a.x)*(a.x) + cosAngle*(1-(a.x)*(a.x));
		m_Values[ 4] = (a.x)*(a.y)*(oneMinusCosAngle) - sinAngle*a.z;
		m_Values[ 8] = (a.x)*(a.z)*(oneMinusCosAngle) + sinAngle*a.y;

		m_Values[ 1] = (a.x)*(a.y)*(oneMinusCosAngle) + sinAngle*a.z;
		m_Values[ 5] = (a.y)*(a.y) + cosAngle*(1-(a.y)*(a.y));
		m_Values[ 9] = (a.y)*(a.z)*(oneMinusCosAngle) - sinAngle*a.x;

		m_Values[ 2] = (a.x)*(a.z)*(oneMinusCosAngle) - sinAngle*a.y;
		m_Values[ 6] = (a.y)*(a.z)*(oneMinusCosAngle) + sinAngle*a.x;
		m_Values[10] = (a.z)*(a.z) + cosAngle*(1-(a.z)*(a.z));
	}
	//-----------------------------------------------------------------------//
	template <class T>
	void CMatrix4<T>::IdentityScale( const CVector3<T>& a_Axis )
	{
		Identity();
		m_Values[ 0] = a_Axis.x;
		m_Values[ 5] = a_Axis.y;
		m_Values[10] = a_Axis.z;
	}
	//-----------------------------------------------------------------------//
	template <class T>
	void CMatrix4<T>::IdentityTranslate( const CVector3<T>& a_Vector )
	{
		Identity();
		m_Values[12] =  a_Vector.x;
		m_Values[13] =  a_Vector.y;
		m_Values[14] =  a_Vector.z;
	}
	//-----------------------------------------------------------------------//
	// http://en.wikipedia.org/wiki/Rotation_(geometry)
	// 
	template <class T>
	inline void CMatrix4<T>::Rotate(T a_Angle, const CVector3<T>& a_Axis)
	{
		CMatrix4<T> rotate;
		rotate.IdentityRotate(a_Angle, a_Axis);
		(*this) *= rotate;
	}
	//-----------------------------------------------------------------------//
	// http://en.wikipedia.org/wiki/Scaling_(geometry)
	// Only support scaling along the x, y and z axis
	// Do NOT support scale along arbitrarily direction
	template <class T>
	inline void CMatrix4<T>::Scale(const CVector3<T>& a_Axis)
	{
		CMatrix4<T> scale;
		scale.IdentityScale(a_Axis);
		(*this) *= scale;
	}
	//-----------------------------------------------------------------------//
	// http://en.wikipedia.org/wiki/Translation_(geometry)
	template <class T>
	inline void CMatrix4<T>::Translate(const CVector3<T>& a_Vector)
	{
		CMatrix4<T> translate;
		translate.IdentityTranslate(a_Vector);
		(*this) *= translate;
	}
	//-----------------------------------------------------------------------//
	inline ISceneBaseNode::ISceneBaseNode() 
		: m_Parent(NULL)
		, m_NodeType(SCENE_BASE_NODE)
		, m_Visibility(true)
	{}
	//-----------------------------------------------------------------------//
	inline const CString& ISceneBaseNode::GetName() const 
	{ 
		return m_Name;
	}
	//-----------------------------------------------------------------------//
	inline void	ISceneBaseNode::SetName(const CString& a_Name) 
	{ 
		m_Name = a_Name;
	}
	//-----------------------------------------------------------------------//
	inline ISceneBaseNode* ISceneBaseNode::GetParent() const 
	{ 
		return m_Parent; 
	}
	//-----------------------------------------------------------------------//
	inline void ISceneBaseNode::SetParent(ISceneBaseNode* a_Parent)
	{ 
		m_Parent = a_Parent;
	}
	//-----------------------------------------------------------------------//
	inline int ISceneBaseNode::GetNodeType() const 
	{
		return m_NodeType; 
	}
	//-----------------------------------------------------------------------//
	inline CString ISceneBaseNode::GetNodeTypeString() const
	{
		switch (m_NodeType)
		{
		case SCENE_BASE_NODE: {
			return _T("BaseNode");
		} break;
		case SCENE_CAMERA_NODE: {
			return _T("CameraNode");
		} break;
		case SCENE_LIGHT_NODE: {
			return _T("LightNode");
		} break;
		case SCENE_GEOMETRY_NODE: {
			return _T("GeometryNode");
		} break;
		case SCENE_GROUP_NODE: {
			return _T("GroupNode");
		} break;
		default: {
			return CString();
		} break;
		}
	}
	inline bool	ISceneBaseNode::GetVisibility() const 
	{
		return m_Visibility; 
	}
	//-----------------------------------------------------------------------//
	inline void	ISceneBaseNode::SetVisibility(bool a_Visibility) 
	{ 
		m_Visibility = a_Visibility; 
	}
	//-----------------------------------------------------------------------//
	inline void ISceneBaseNode::Translate(const CVector3f& t)
	{
		m_LocalMatrix.Translate(t);
	}
	//-----------------------------------------------------------------------//
	inline void ISceneBaseNode::Rotate(float angle, const CVector3f& axis)
	{
		m_LocalMatrix.Rotate(angle, axis);
	}
	//-----------------------------------------------------------------------//
	inline void ISceneBaseNode::Scale(const CVector3f& axis)
	{
		m_LocalMatrix.Scale(axis);
	}
	//-----------------------------------------------------------------------//
	inline void ISceneBaseNode::GotoLocalOrigin()
	{
		m_LocalMatrix.Identity();
	}
	//-----------------------------------------------------------------------//
	inline void ISceneBaseNode::GotoWorldOrigin()
	{
		// TODO:
	}
	//-----------------------------------------------------------------------//
	inline const CMatrix4f& ISceneBaseNode::GetLocalMatrix() const
	{
		return m_LocalMatrix;
	}
	//-----------------------------------------------------------------------//
	inline const CMatrix4f& ISceneBaseNode::GetWorldMatrix()
	{
		UpdateWorldMatrix();
		return m_WorldMatrix;
	}
	//-----------------------------------------------------------------------//
	inline void ISceneBaseNode::UpdateWorldMatrix()
	{
		if (m_Parent == NULL) {
			m_WorldMatrix = m_LocalMatrix;
		} else {
			m_WorldMatrix = m_Parent->GetWorldMatrix() * m_LocalMatrix;
		}
		
	}
	//-----------------------------------------------------------------------//
	inline ISceneGroupNode::ISceneGroupNode()
	{
		m_NodeType = SCENE_GROUP_NODE;
	}
	//-----------------------------------------------------------------------//
	inline void ISceneGroupNode::AddChild( ISceneBaseNode* a_Child )
	{
		if ((a_Child == NULL) || (a_Child == this) || (a_Child->GetName().IsEmpty())) {
			return;
		}
		if (m_Children.find(a_Child->GetName()) != m_Children.end()) {
			return;
		}
		a_Child->AddRef();
		a_Child->SetParent(this);
		m_Children.insert(std::make_pair(a_Child->GetName(), a_Child));
	}
	//-----------------------------------------------------------------------//
	inline ISceneBaseNode* ISceneGroupNode::GetChild( const CString& a_Name ) const
	{
		if (a_Name.IsEmpty()) {
			return NULL;
		}
		auto it = m_Children.find(a_Name);
		if (it != m_Children.end()) {
			return it->second;
		}
		return NULL;
	}
	//-----------------------------------------------------------------------//
	inline const ISceneGroupNode::NodeTable& ISceneGroupNode::GetChildren() const
	{
		return m_Children;
	}
	//-----------------------------------------------------------------------//
	inline void ISceneGroupNode::RemoveChild( ISceneBaseNode* a_Child )
	{
		if ((a_Child == NULL) || (a_Child == this)) {
			return;
		}
		for (auto it = m_Children.begin(); it != m_Children.end(); ++it) {
			if (it->second == a_Child) {
				it->second->Release();
				m_Children.erase(it);
			}
		}
	}
	//-----------------------------------------------------------------------//
	inline void ISceneGroupNode::RemoveChild( const CString& a_Name )
	{
		if (a_Name.IsEmpty()) {
			return;
		}
		auto it = m_Children.find(a_Name);
		if (it != m_Children.end()) {
			it->second->Release();
			m_Children.erase(it);
		}
	}
	//-----------------------------------------------------------------------//
	inline ISceneCameraNode::ISceneCameraNode() : m_Fovy(0.0f), m_ZNear(0.0f), m_ZFar(0.0f)
	{
		m_NodeType = SCENE_CAMERA_NODE;
	}
	//-----------------------------------------------------------------------//
	inline float ISceneCameraNode::GetFovy() const
	{
		return m_Fovy;
	}
	//-----------------------------------------------------------------------//
	inline void	ISceneCameraNode::SetFovy(float a_Fovy)
	{
		m_Fovy = a_Fovy;
	}
	//-----------------------------------------------------------------------//
	inline float ISceneCameraNode::GetZNear() const
	{
		return m_ZNear;
	}
	//-----------------------------------------------------------------------//
	inline void	ISceneCameraNode::SetZNear(float a_ZNear)
	{
		m_ZNear = a_ZNear;
	}
	//-----------------------------------------------------------------------//
	inline float ISceneCameraNode::GetZFar() const
	{
		return m_ZFar;
	}
	//-----------------------------------------------------------------------//
	inline void	ISceneCameraNode::SetZFar(float a_ZFar)
	{
		m_ZFar = a_ZFar;
	}
	//-----------------------------------------------------------------------//
	inline const RECT& ISceneCameraNode::GetRect() const
	{
		return m_Rect;
	}
	//-----------------------------------------------------------------------//
	inline void	ISceneCameraNode::SetRect(const RECT& a_Rect)
	{
		m_Rect = a_Rect;
	}
	//-----------------------------------------------------------------------//
	inline void ISceneCameraNode::LookAt( const CVector3f& a_Position, const CVector3f& a_FocusPoint, const CVector3f& a_UpVector )
	{
		m_LocalMatrix.LookAt(a_Position, a_FocusPoint, a_UpVector);
	}
	//-----------------------------------------------------------------------//
	inline IWindow32::IWindow32() : m_RootSGNode(NULL), m_ActiveCameraNode(NULL), m_GUIEventHandler(NULL)
	{}
	//-----------------------------------------------------------------------//
	inline ISceneGroupNode*	IWindow32::GetRootSGNode() const
	{
		return m_RootSGNode;
	}
	//-----------------------------------------------------------------------//
	inline void	IWindow32::SetRootSGNode(ISceneGroupNode* a_RootSGNode)
	{
		if (m_RootSGNode != NULL) {
			m_RootSGNode->Release();
		}
		m_RootSGNode = a_RootSGNode;
		if (m_RootSGNode != NULL) {
			m_RootSGNode->AddRef();
		}
	}
	//-----------------------------------------------------------------------//
	inline ISceneCameraNode* IWindow32::GetActiveCameraNode() const
	{
		return m_ActiveCameraNode;
	}
	//-----------------------------------------------------------------------//
	inline void	IWindow32::SetActiveCameraNode(ISceneCameraNode* a_CameraNode)
	{
		if (m_RootSGNode != NULL) {
			m_RootSGNode->Release();
		}
		m_ActiveCameraNode = a_CameraNode;
		if (m_ActiveCameraNode != NULL) {
			m_ActiveCameraNode->AddRef();
		} 
	}
	//-----------------------------------------------------------------------//
	inline ISceneLightNode::ISceneLightNode()
		: m_Ambient(0.0f, 0.0f, 0.0f, 1.0f)
		, m_Diffuse(1.0f, 1.0f, 1.0f, 1.0f)
		, m_Specular(1.0f, 1.0f, 1.0f, 1.0f)
		, m_Position(0.0f, 0.0f, 1.0f, 0.0f)
		, m_SpotDirection(0.0f, 0.0f, -1.0f)
		, m_SpotExponent(0.0f)
		, m_SpotCutoff(180.0f)
		, m_Attenuation(1.0f, 0.0f, 0.0f)
	{
		m_NodeType = SCENE_LIGHT_NODE;
	}
	//-----------------------------------------------------------------------//
	inline int ISceneLightNode::GetID() const
	{
		return m_ID;
	}
	//-----------------------------------------------------------------------//
	inline const CVector4f&	ISceneLightNode::GetAmbient()
	{
		return m_Ambient;
	}
	//-----------------------------------------------------------------------//
	inline void	ISceneLightNode::SetAmbient(const CVector4f &a_Ambient)
	{
		m_Ambient = a_Ambient;
	}
	//-----------------------------------------------------------------------//
	inline const CVector4f&	ISceneLightNode::GetDiffuse() const
	{
		return m_Diffuse;
	}
	//-----------------------------------------------------------------------//
	inline void	ISceneLightNode::SetDiffuse(const CVector4f &a_Diffuse)
	{
		m_Diffuse = a_Diffuse;
	}
	inline const CVector4f& ISceneLightNode::GetSpecular() const
	{
		return m_Specular;
	}
	//-----------------------------------------------------------------------//
	inline void	ISceneLightNode::SetSpecular(const CVector4f &a_Specular)
	{
		m_Specular = a_Specular;
	}
	//-----------------------------------------------------------------------//
	inline const CVector4f&	ISceneLightNode::GetPosition() const
	{
		return m_Position;
	}
	//-----------------------------------------------------------------------//
	inline void	ISceneLightNode::SetPosition(const CVector4f &a_Position)
	{
		m_Position = a_Position;
	}
	//-----------------------------------------------------------------------//
	inline const CVector3f&	ISceneLightNode::GetSpotDirection() const
	{
		return m_SpotDirection;
	}
	//-----------------------------------------------------------------------//
	inline void	ISceneLightNode::SetSpotDirection(const CVector3f &a_SpotDirection)
	{
		m_SpotDirection = a_SpotDirection;
	}
	//-----------------------------------------------------------------------//
	inline float ISceneLightNode::GetSpotExponent() const
	{
		return m_SpotExponent;
	}
	//-----------------------------------------------------------------------//
	inline void	ISceneLightNode::SetSpotExponent(float a_SpotExponent)
	{
		m_SpotExponent = a_SpotExponent;
	}
	//-----------------------------------------------------------------------//
	inline float ISceneLightNode::GetSpotCutoff() const
	{
		return m_SpotCutoff;
	}
	//-----------------------------------------------------------------------//
	inline void	ISceneLightNode::SetSpotCutoff(float a_SpotCutoff)
	{
		m_SpotCutoff = a_SpotCutoff;
	}
	//-----------------------------------------------------------------------//
	inline const CVector3f&	ISceneLightNode::GetAttenuation() const
	{
		return m_Attenuation;
	}
	//-----------------------------------------------------------------------//
	inline void	ISceneLightNode::SetAttenuation(const CVector3f& a_Attenuation)
	{
		m_Attenuation = a_Attenuation;
	}
	//-----------------------------------------------------------------------//
	inline ISceneGeometryNode::ISceneGeometryNode()
	{
		m_NodeType = SCENE_GEOMETRY_NODE;
	}
	//-----------------------------------------------------------------------//
	inline IGUIEventHandler*	IWindow32::GetGUIEventHandler() const
	{
		return m_GUIEventHandler;
	}
	//-----------------------------------------------------------------------//
	inline void	IWindow32::SetGUIEventHandler(IGUIEventHandler* a_GUIEventHandler)
	{
		m_GUIEventHandler = a_GUIEventHandler;
	}
}