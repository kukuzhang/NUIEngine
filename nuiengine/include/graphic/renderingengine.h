V�l�1�1��#B1R�`�sGP�E�R@f='�GL�����c�	&P�T�4B0���S�J4>��oTz�+V�X�w-o<r�áz���]��p����I0w����i-�U�R�?���/���δ�ᔶm��z�bH$+s��o�{�.�7Q�g��!N��S�[ť�]L�7f9&���1lK)fh�2�o@y���O)1�T`��!_J�YX�ZT�m�Y"A�Ca�Y�-�!�e�qW=s�Co�Bّ�+%w�'�l�����J6,� ݲԖ�W쳬��J����rN��ۊϛ+�/f�����$�]��}/���Wø1��`�f� �ӒB��'"�6��V�!�/��KzS��o��(�1�$g<����=y+T���7E�42���8�
9��N��O�-Y
C�׃Z�������݂J�
˫�w��21��ڌ�/��Lo�Y�i߬��^�0��.vړE�#+�|� ��X�sIԭ$��R�r��|/���eR��"H4�1V<�ڕXX�/�,��<bI��J�TH�� P=(^�rnm�!̈p}��<QT 	d,�F
��wK1�c+'�ԗ�(���ǡ�^�k��H��2ߧ_$��Yd-/�$v��� ��?�m<H��ź�����\��8�u�yZk8���Ք�l���7�*ϯt�:}�,<�����W*g��-ʄҗC��J��J�W��l�8@��sS}�y����n0kH��ob�J�	�V�F��q�4<Lb�]yS�Zx%���<�k�N���m�T�֢��V��9�FL!����/(m���SC��k������saz��c�iLi4^����Vx���P���"����)�C&Onj$�$
�J��})���d{PwP,���<l6���;�"�Z���c'J����3�� ����B��6�*��ZZm-t���%-9�]p�#Ҕ(ڸR��[
ZJ�`-0mN��ޱ�Ѧ1▐R�&�7�M������O�>��;U���<SN�Ղ����F��g� Qyxx�7��� ��hn�T�� ��������@�T�G�Q���Z@V�@�X�6�I;�s��S'G��ml��I����PG
��F)�F���HM �f=��q��RȺ�c=����Xn�i�K.NEeg���4Dc�9���2wHm��G(,��<���f�X�!U��=�+3s+��]GQ�Ϧ��h/%��E�dVV ���G�Dq[�ia�FY��?�dElJ̲�VVD ��Q^\���v
}<��Q��Q��3�w�խ +����*Y���Rőqgp��[tU70��)?.��o,���vS.�B�ه��Is����������.�Ҥ�j�d�]$�<VnM��E'E�A�[�|Dč�K�p�� ?֬��`��]�'CH�7��N���4fGQ�r}����5t���*��iQ���ߝew����E/P��[�X�>\eO�U�d�yUá��� ��;+��i�g.p�}�V���ćNw=�<�xGEb��1-X�}�9�Fs��5_},�-�6]/.�Ƭ����F`2�>��ܹKg��������X%�c_,{�Tq6�W<W��Y��rF��WJ�'���ǵzP[<|��i�i����N2�cڀ�6��4@�_J��yF��~ul�J�$xi �����0�X:�	�@���,|�ۚ���'�K��`s����Td� ��B��s�h������+#�7�	>Q+���0� g2�e;�NƢI^�?.�ң�Vf 횾�kV
m�F#NpjנH��u�TIn�3�����g4�eR�5�k��R�h:$2JH�����=�Z����Ҁ��Eco:��D"�HA��Z�X�j��bQ6�@���Fos�Q��Ayt��ުI�;�NM�B���,I4���m K�;f�4 ���	��t�V�\g>�5J�h&�oN�\��2��C�����-�1DA�����E�)��D�*^��I9,�d��"�Xt��=�U���� T!�:�+p`U�1��cs�'�������M���=j.�r{T$���*[�Z�I�f����vaV�Sbf=�*��Bu-+�ލ�$����L���>����O���;So���j����-U�o�l��LI��y*�t_�aWs��[WM��)IZ�'�z�JF�x��(Ǳ�DѹFe8 ��N�r�yvչ�/_�"��c����[+TT�i��Z�!]���ԝ��Ȧ"a��CS�L0ؒA�+H�I�[85��Q�A���
N��* %��N��)P�Q��*J�����*6
�C.w��c��CQ�5E.}i � δ�i �#��Cxw�2}���hD���V�ڞ�ʚ��aB������S�o����                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 t, size_t count, kn_bool bClose, const REPaint& paint ) = 0;

	// 多点绘制, 支持点, 线, frame模式
	virtual void DrawPonits(SkCanvas::PointMode mode, size_t count, const REPoint pts[], const REPaint& paint ) = 0;

	// 绘制圆
	virtual void DrawCircle(REScalar x, REScalar y, REScalar radius, const REPaint& paint) = 0;
	virtual void DrawArc(RERect& oval, SkScalar startAngle, SkScalar sweepAngle, bool useCenter, SkPaint& paint) = 0;

	// 绘制位图, 将整张源图绘制到目标图上(left(), top())位置
	virtual kn_bool DrawBitmap(const IRESurface* pSourceRE, 
		REScalar left, 
		REScalar top, 
		const REPaint* pPaint = 0) = 0;

	// 以变换矩阵的方式绘制位图
	virtual bool DrawBitmapMatrix(const IRESurface* pSourceRE, const REMatrix& m, const REPaint* pPaint = 0) = 0;

	virtual void drawBitmapNine(const IRESurface* bitmap, const RERect& center, const RERect& dst, const SkPaint* paint = NULL) = 0;
	
	// 绘制位图, 将整张源图的部分srcRect绘制到目标图上(left(), top())位置
	virtual kn_bool DrawPartialBitmap(const IRESurface* pSourceRE, 
		RERect srcRect,
		REScalar destLeft, 
		REScalar destTop, 
		const REPaint* pPaint = 0) = 0;

	// 绘制位图, 支持拉伸
	virtual kn_bool DrawBitmapRectToRect(const IRESurface* pSourceRE, 
		const RERect* pSourceRect, 
		const RERect& destRect, 
		const REPaint* pPaint = 0) = 0;
	//指定位图以指定填充方式绘制到画布
	virtual void DrawPaint(const REPaint& pPaint) = 0;
	// 绘制文字
	virtual void DrawText(const void* text, size_t byteLength, REScalar x,
		REScalar y, const REPaint& paint) = 0;
		virtual void DrawText(const kn_string& text, REScalar x,
		REScalar y, const REPaint& paint) = 0;
	// 沿轨迹绘制文字
	    /** Draw the text, with origin at (x,y), using the specified paint, along
        the specified path. The paint's Align setting determins where along the
        path to start the text.
        @param path         The path the text should follow for its baseline
        @param hOffset      The distance along the path to add to the text's
                            starting position
        @param vOffset      The distance above(-) or below(+) the path to
                            position the text
        @param paint        The paint used for the text
    */
    virtual void DrawTextOnPathHV(const kn_string& text,
                          const REPath& path, REScalar hOffset,
                          REScalar vOffset, const REPaint& paint) = 0;
	/** Draw the text, with origin at (x,y), using the specified paint, along
    the specified path. The paint's Align setting determins where along the
    path to start the text.
    @param path         The path the text should follow for its baseline
    @param matrix       (may be null) Applied to the text before it is
                        mapped onto the path
    @param paint        The paint used for the text
    */
    virtual void DrawTextOnPath(const kn_string& text, size_t byteLength,
                                const REPath& path, const REMatrix* matrix,
                                const REPaint& paint) = 0;

	// 保存当前的matrix和clip
	virtual int Save() = 0;

	// 还原save时的matrix和clip
	virtual void Restore() = 0;

	// 裁剪矩形
	virtual bool ClipRect(const RERect& rect,  RERegion::Op op = RERegion::kIntersect_Op, bool doAntiAlias = false) = 0;

	// 保存surface到文件, 缺省格式为PNG, 支持JPEG
	virtual bool WriteToFile(const kn_string& path, REImageEncoder::Type type = REImageEncoder::kPNG_Type, kn_int quality = 100) = 0;

	// 绘制上屏
	virtual void Flip(LSTRECT &lst_rect) = 0;

	// 绘制椭圆
	virtual void DrawOval(const RERect& oval, const REPaint& paint) = 0;

	// 绘制圆角矩形
	virtual void DrawRoundRect(const RERect& rect, REScalar rx, REScalar ry, const REPaint& paint) = 0;

	// 绘制轨迹
	virtual void DrawPath(const REPath& path, const REPaint& paint) = 0;

	// 平移
	virtual bool Translate(REScalar dx, REScalar dy) = 0;

	// 缩放
	virtual bool Scale(REScalar sx, REScalar sy) = 0;

	// 旋转
	virtual bool Rotate(REScalar degrees) = 0;

	// 倾斜
	virtual bool Skew(REScalar sx, REScalar sy) = 0;

	// 获取画布矩阵
	virtual REMatrix GetTotalMatrix() = 0;

	// 设置画布矩阵
	virtual void SetMatrix(const REMatrix& m) = 0;

	// 变换画布矩阵
	virtual void Concat(const REMatrix& m) = 0;

	// 还原画布矩阵
	virtual void ResetMatrix() = 0;

	//绘制的预处理，screen的draw调用，用于硬件渲染的环境预设置
	virtual void preDraw() = 0;

	virtual REColor getColor(int x, int y) = 0;

};

// 第一个版本的RESurface Factory, 基于Skia2D引擎
class NUI_API RESurfaceFactory
{
public:
	// 获取新的surface
	static IRESurface* CreateRESurface();

	// 获取新的surface并立即进行初始化, 假如初始化失败, 则返回空指针
	static IRESurface* CreateRESurface(kn_int width, kn_int height, REBitmap::Config colorFormat);

	static IRESurface* CreateRESurface(void* p, kn_int width, kn_int height, REBitmap::Config colorFormat);

	// 获取新的surface并立即从文件进行初始化, 假如初始化失败, 则返回空指针
	static IRESurface* CreateRESurface(const kn_string& filePath);

#if defined(WIN32)
	// 创建Win32上屏surface
	static IRESurface* CreateDeviceReSurface(HDC,kn_int width, kn_int height, REBitmap::Config colorFormat);
	static IRESurface* CreateLayerDeviceReSurface(HWND wnd, HDC hdc,kn_int w, kn_int h, REBitmap::Config cf);
	static IRESurface* CreateDDrawReSurface(HWND,kn_int width, kn_int height, REBitmap::Config colorFormat);
	static IRESurface* CreateGLReSurface(HDC,kn_int width, kn_int height, REBitmap::Config colorFormat);
	static IRESurface* CreateSkiaGLReSurface(HWND wnd, kn_int w, kn_int h, REBitmap::Config cf);
	static IRESurface* CreateGLLayerDeviceReSurface(HWND wnd, HDC hdc,kn_int w, kn_int h, REBitmap::Config cf);

#elif ANDROID_NDK


	static IRESurface* CreateAndroidReSurface(char* buff, kn_int width, kn_int height, REBitmap::Config colorFormat);
    
#elif IOS_DEV
    
    static IRESurface* CreateIOSReSurface(void*& buff, kn_int width, kn_int height, REBitmap::Config colorFormat);
    

#elif QT_HMI

    static IRESurface* CreateQtSoftReSurface(void* p, kn_int width, kn_int height, REBitmap::Config colorFormat);

#endif

};

}
#endif
