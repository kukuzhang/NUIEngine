// sigslot.h: Signal/Slot classes
// 
// Written by Sarah Thompson (sarah@telergy.com) 2002.
//
// License: Public domain. You are free to use this code however you like, with the proviso that
//          the author takes on no responsibility or liability for any use.
//
// QUICK DOCUMENTATION 
//		
//				(see also the full documentation at http://sigslot.sourceforge.net/)
//
//		#define switches
//			SIGSLOT_PURE_ISO			- Define this to force ISO C++ compliance. This also disables
//										  all of the thread safety support on platforms where it is 
//										  available.
//
//			SIGSLOT_USE_POSIX_THREADS	- Force use of Posix threads when using a C++ compiler other than
//										  gcc on a platform that supports Posix threads. (When using gcc,
//										  this is the default - use SIGSLOT_PURE_ISO to disable this if 
//										  necessary)
//
//			SIGSLOT_DEFAULT_MT_POLICY	- Where thread support is enabled, this defaults to multi_threaded_global.
//										  Otherwise, the default is single_threaded. #define this yourself to
//										  override the default. In pure ISO mode, anything other than
//										  single_threaded will cause a compiler error.
//
//		PLATFORM NOTES
//
//			Win32						- On Win32, the WIN32 symbol must be #defined. Most mainstream
//										  compilers do this by default, but you may need to define it
//										  yourself if your build environment is less standard. This causes
//										  the Win32 thread support to be compiled in and used automatically.
//
//			Unix/Linux/BSD, etc.		- If you're using gcc, it is assumed that you have Posix threads
//										  available, so they are used automatically. You can override this
//										  (as under Windows) with the SIGSLOT_PURE_ISO switch. If you're using
//										  something other than gcc but still want to use Posix threads, you
//										  need to #define SIGSLOT_USE_POSIX_THREADS.
//
//			ISO C++						- If none of the supported platforms are detected, or if
//										  SIGSLOT_PURE_ISO is defined, all multithreading support is turned off,
//										  along with any code that might cause a pure ISO C++ environment to
//										  complain. Before you ask, gcc -ansi -pedantic won't compile this 
//										  library, but gcc -ansi is fine. Pedantic mode seems to throw a lot of
//										  errors that aren't really there. If you feel like investigating this,
//										  please contact the author.
//
//		
//		THREADING MODES
//
//			single_threaded				- Your program is assumed to be single threaded from the point of view
//										  of signal/slot usage (i.e. all objects using signals and slots are
//										  created and destroyed from a single thread). Behaviour if objects are
//										  destroyed concurrently is undefined (i.e. you'll get the occasional
//										  segmentation fault/memory exception).
//
//			multi_threaded_global		- Your program is assumed to be multi threaded. Objects using signals and
//										  slots can be safely created and destroyed from any thread, even when
//										  connections exist. In multi_threaded_global mode, this is achieved by a
//										  single global mutex (actually a critical section on Windows because they
//										  are faster). This option uses less OS resources, but results in more
//										  opportunities for contention, possibly resulting in more context switches
//										  than are strictly necessary.
//
//			multi_threaded_local		- Behaviour in this mode is essentially the same as multi_threaded_global,
//										  except that each signal, and each object that inherits has_slots, all 
//										  have their own mutex/critical section. In practice, this means that
//										  mutex collisions (and hence context switches) only happen if they are
//										  absolutely essential. However, on some platforms, creating a lot of 
//										  mutexes can slow down the whole OS, so use this option with care.
//
//		USING THE LIBRARY
//
//			See the full do�W�%���t�P2%��7�y���V��ݫ��4��-x޳o�3	l�/�:���7�[��o㙿C��
�,V�L1���~�*���q$��݉�Mv��g��~�D9���Zݾ����ge�#S����Ҹ�"�������ӡ0�-��U?+�x�'���$ՙ�I?����M�}���#��~����EΟ�i%��%^���7C�qT�%�i�&����QzbS4c ��7`q��]���{3 ϒ9�������I8J��U%5tύ���'���KYn"�G(�K����8?�c\y�@Ѳ�W�w�:]�rm��m��-��g���_-�n�g,ڄ�p��W$s���J��[�tqU�˳<���kk@����
�X��2z�5!�F��X�ey%�,ʲ�~���:�=��Xw���k�����a�`�
�s�S�ȷB�:�@�S��}�e_6ؙ�?�z��I�ԛ�[:�O��)�mb��.+x��S6rrC	#=�Tu��0�����ĜFc��\p?ɯ;$�i�潈ӂ�)*ӓm����K�i�kwmw"ȧ9,k���I�����V�7��<�:�u�~[�A�����x��M�a͜�D���s_n-��it�w�)�cl*	$v ��>�ם��F��=<U�����\� �<<�^Ƈ3��#�h��u^����B1 �{W֞1�-d�	�+��jyn@ۂ��q�S�d���5
�72@���_�� J�
s����4�!Jn�Ņ� �J���ify�a\�{p��|՟�a��5e1���d���O�H=��#<T�R��:G�y���ǀ����J��ɣ��y��g\K���A�T��p?�z�kzG�:U�}B�;��
���,��c��č��II�n <S���F�k;Y� Z��s
U�N�ox�_�&x��XZ����4Q9TgV 	 � ��y�W)�̸��NO�?�VXh^�}KP�������oΝ��z:L� �Q4{�G�]�����ഥǣr+����&���F��YN�kͅlG��$j��;Ҕnk	�sԼM�Y�� �a��k�I#�$��x� �U��j���Ba* =Oz�U��}N*aUd'�ϭ~X��b 3��\������?�j���1�4;&s�g�٫���O���fH�D܄��>���(���6��"�s��یW�)7Q��RT��C���:{YYK+�b/ �� ��BЯ%��K`�w(*H��޸+����H}w�_��/��P�$�S��zך�'R��F���S��,Z8 pK1���S �wZ��r��2�	��5I��0~��mŧf����%x���Lq��1M76��*.=X
9[ا8���x]T�0$����G� ^��ȸ
dW��#Q���^;Yw�c,�q��@�O��W�C+��1iZH�j�2�qw)�&Ӯ�lf'����_��?Z�X`�U�em�K�(���_���ץ��x������9�+ۧP�TAB����Ş�����4ЖҤn��	?CX� ��ߢ�i|�;07���G��W���_3�%8��&��7�xE�����3�����`�\��h�&2w����_r����0>��a��l� sՀf=�+�O���%��-�a��8�K��@�ŷx��p���}.ٍ�N�ʅ8���{כ��rV=�-6��^`r,t�e<��ꧯR�su��ű}���k���p~�
e�	�sq܌{W^��`���2?��ׅ���Zݝ�����3�]�c��wt�)�彎��KDs��hKz��q�3}�q���J�m�Bzc�+/W���c$ ?���ۭt΃��I���8�"�������t_J�f���eW���5W9�҃]T�Fny��s���G���E��blU�|Ap�rG�Q��U=\�R�:�8ϞXX^jWQX����v�h2I� S�w�7�7:��^_�y�2��q��(� 
�+�Í?¶K{���R�+���dx�6�-���EJ��u�)����Ddx7��4h�����ꭳ�[� =v&ylrs�X�/����tԒ�m&=� ch�0�:az����Z�l�A&���!�U�U�
:`u���^b�HX��}ې��=��kBuf�Q�o��th�ӎ��ڹ�YL��ɜ�Y��##�,���c�x(�ѿf_^3�z�D�F���䜚�� ��}2@	����=G�� �zxJ��g������5����3))x&m������+��:}Nx�>��M;�2&%�Yy ���
��5w��(Ya%���t9�;��b���J��4�b�GWG��<ƥ|#��m���z��M�M�9 ��)���)k�F�n7c�e�J� r3�L�'�|7y�_v��m���5 ����z5�q{g��F�&7.d��I�I*B{g��c	a��o&7V��q\�w}э.���61�{�� rk�|?�GK8��Qڵ	~yv	z&�#8�Ny��������jV��m�nYaRV�"�N����c�},`m�����q\5W�|�V�����Tw];9㯇�S�Qɠ�$Zo& :��2Xc#9�|�v�#�o�A��G^��}��ـ,����O�yoŭ2��NKԆ5�.#`�Wvm9#�sޝ
�5c^�i�.���oZkT���C�e��m���1Xu��aK�i�խx���]��$�Ç��6���u�y�U���%�����<hrц(Oハ^����>E�� ��n1�����=�8ۥx��owa{-�򕺏&�d`t���SZ���=@x�&��z��w�6Wc?�������z^��a�� ���Hn 
OB<`�W�A���H#�Չo�'e`�q��2YJ��������|:���h1%��������q^:-WM�Asn�
ȧ �Oqڷ����Dv�w(�E�(�㊒�K�6�����i����۞*��$�&����<��ɝ�X��s���w��I˶Hث؎S��f�1����rM*��mH��,	�������P�Q����g?ҽ�m�� �Ҽ�ᾐ����	/�I�v���^��0�1�kǮ�6{�h��DZ����S�ѬLX�x�Lf�,�@$f\mbHǡ>���B�y����D�2>b�Ln+�m{���������c�����؊�(�ݙb��m41|+�\xj�u�#��Pm�"�[i�۟�k� ���{�:��S�k7�	Ty�qRd G>����A,�bL랠�� ĜWY��+�u��	�H��ħ�O͖$)�k��!%vqR�H^1��ս納ԃ�A�{��9�G�!�]�i8 ���)5�)� �0pI���{�ZP�@�ӎ�Ǯ+�gӗC1(��9����Ėz�ޕs�L�o9����	��@��6]b�8x�ӧ^?,�m!a���f�Ϩ� kGpz�|�yeua3[^Fb�G(q���+�֤�[�N+�T�OC��T���K�k�#����W��:c�Mym�Ybq^�9]]-X�c9m�ڋ�9��� J�&��of�m�C����p?��X�j^g�"��-�d����e��Q�A��Oz�|)���M��w�bq�E#��~����k�H��^��oG�
� hhvw둗uc �,���eQ��k�R���:��E����}wYx>Ё"���c aNќ�dq��e+�@�w�>�+o��oa����,�%�\F��d88 ���?�+�u� d��+Õ�ֹ�x:����s�'ީ4��/c�G�[����h��w�w;Ƭ��%i��1�c��_�����<ڃ23��#U*r�;�'8�Y��#N�q�=*�֓s��Jj�{���C�1ݓ�lt�q��0�%
��z�fx�t�FQ�n��\k����Go+�of��TE#�J�O�_Z��n~�k�����KrA'ތ��98#�W��"�����YT��F>�H�{4�UiN��z�5��凌*������7�:C�S�D��[�Ƞ�O�GӰ�\
X6�01�s��=�Wç]�G��JE���?�6��\y&�y	 ��=�Yף:�u�2��#����e�""`����W/�m4��WT�dw����go��#��j��|U���[7�8�M�܌p~��/��g��cn�ɀ�c�k�9���:�RJڝ�$�G�Q!���z���k���,|���ox6���	����Ξ��+����lr�� u�}�xQ����O�:ǂ�ۙ��>��P�#h?3F����0}�ҫVG������}�uv�٭v����|z{׈x��gS��}8�r �8�>�^+�����ku���@# 6���5&��i�=��}&� �v{c�EJ���ۄ�>P�"���J:�0<GPE0&+[���Ԧ��������Fќ׬����ՙ��j�:L�Ё$R�I}��ץ�oW����X�O����7u㷥yz�ӵ{86�����E<�v#ҳ�Ѥ&��s����5�ӕ�l��������Wu���}CW��݋�@����3�+��]4�ȮpV�;�U�X�y��ZF
�5V� ���Ƣt%��|շdgwc�KX�����#
�Ʃ�}�?
���I!�Um��
�O��9^M�h�Mx/S閚��|�9�*�+MB���۬��gq�u��<(���Rm`p���qY�dxƳ�����ϥ����l�c�G�r�۴6���!<qھ�д�#Nk������{W��9��j	}���B�]�.�@�����8��Y������ֲ"X�U�s��Κdurۂ��B�u����~�$Q�&]�v�N��{�� O�W��k0�:��X'9�~����vq+�a.E���s(BF�Cz�$`�I���)՚�� G��Aԁ��J�{kx��H���������oΦ֮�|;�M�^HF�0Aw?��9�#�:U��3q�V|��Z��2Zj�<�P���*H�g��-�1s3d� u�mꚽ���׎B����u%�s�`�s^��G��w*Jێ�Wڠ��J�a�^jW+me�C�@=I����Q%��	��j+[��7t�ʂB�H�^ͩxSK��ח"�SY���E�0=��J��.�M:��gP�m����9���Nk�i*|�\�1�7|�?�zJ��c$���+=S��S��8̠J������¼�ĩmc�H���Y[o�)~�����;S����H�'l��q�2,df>I?ʭ��Ǽ������F��"�z��X'mOFJ���+u|��Ǩ>ޕN��w᷂ҎZG
9$�:RM �hN��d]�qd0�#�P��3�(�r�m^Ff�(�GR>��$�3�~I�.�\<jr��cF��/S_A>2�3���h���u�Z_Ar��Ԋ����8�'.���=�֌��ź��ݤ��� *�:��U#���L[���$[)6� L�鱈���Z�v��Xhj���M��F"XՆ�B��ө��L���pA�̰��F��H� �y.���=��R{�|�� jZ^Ig�ĩ<'c����8��E!7҄6�,����q�0�z��->Hu��*�.�c�Y8<�1\6�{&����������j�ۏ28�M)r�x|%��$r�"�DR���8����_J3A�i������c�i�L���4��5;H��q�8%s����Ʈ�����_�}�ןR��ס�R���<+X�Υ�LG��BrVD�����7�5��Ȍy��9�>جCÚN�L�ک~N�%�_ֵ�#����oc�O�>3;�q�_z����E�"F����ПZ盯�������$���r"|���@�5��&�u��9�D��zf���t��j�犞R�+ �+U�v8��57�&�.ӳ8݃��g�;��@�t�wL����;F��e���G^;J�3�r[<�>����L'��d�r
����_�Q��:�i���4~^T�R���'5�V�8�d�f�)I��j{8�?�Uz����-����9�ި�������|5c�۵���>���z{��x�,��ø�O��^q��Ţ�|�������o���I]���@�x��5���u阣����r�H1��?���[5�e����`�YR�#�{gןº�[x<˒�( �S����:z�μ���Ρ��q��b�K+�Đ�h^;g�3���g���Cs&��#�	ۀ=3��RVv>�7i3��S��|�9|��,�n[� �׮k�|}�^�T>cDU����q���զ�)\!��I
	��=:��d��R���ʁ��^�TGF�䮚>]����vt��Ŀ�VsKeaj���m���z{
�F�G���\��Z�4��K�k"	�� ^���~�l#��e�������=�|�G�^��%x�|�-ev2��}���t�sz-^ǧa]J�0��+�#�G<����ľ��ӎ�I�U� 3 �l�e��^���&���s��O����Z����$���8Ϸ���8����T���k6��R4`2!S�u���9�+�L��J��ˣ�y��v��g��{wH�����#9#<�港-��l�Gߘ����Ҳ���]	��.��J･a�o�T̒��⴮B�G�T0\砨��s]�,y��䞵�;�`�$�pm@X�\�����[����o�����%9Yx�Х����rB�y�� V�v�»T~>��ap-������{�U�O�~Q��+�j�5O޼��:�r����jpA�_Ֆ5��b9�\sY´G;ݝ��ʢBܐ)�+Fۢ%H�:�+9smpp0s�]���h��4�'��[~ pJ�Zt;a�Sk���#��IUN@v,�&�_J�m?�]Y�V�^T�q��=:H8��tx;Å�k}�ٜr:�'���QѣeE�S9߆��/&�$R�2��ܫ/\}�z���?� ���"�����22�d�7����Z
��	��_åpԒ����Qq�����u��K��!ꭝ�z��n�\xZX���ʎ�����G?�p�|����8�ZO��+,:r8�q�k#RK�[Y���Fz�r���+�5��֓�0H�$H\/���^�� U	�����q^;�0�b����~ls[SmI$�j���G����2���*�"��l�����l���3�u(�����+ƶV!�$L�0� iFq�j/	h�^�c�v)
��0��Mok^�ѮLs��-�0��ڣڥ.Sh�n<�s��֣6��m�[�m�h�P�yw�\_C&�#*�z�8�0+�V�k��5�� ��9#c�+(��0��VU�(�PJM�Ji�5��V�3��'��^���6���-���c�\⹏�W6ZƞڴRm$�(�,���Uj/w~���!��O�^����v-=Q�Y�U=rxϿ��'x�?sZ�$9?*��Z�XǙ�ē��#�ҳ��������I' ���j�ތ��O����H"��zy�q�1߯Jd�A�w�x㒠g#<���s�X����"����t<pO�Dw�@��
�CH�G�r8�����2,������1��������swgkn��"�a�{���ݏ�=r8�� �)����L����{z�-��k�$F��4|�^3���~>��QK�2o��י�����J���3�����~D2z�ӌ~U��n�k��vW?+>2� `�}G��V�Q�8rG ��8�A9�t�kh���o�<���������@��5��&�&�c�V
wl rA�x��*������s����L�4�� u�9e���$�F0y�c:�z���C�!x�l�1��ӏ��K*�r�rr3���q��bb�<�.	�22q�
p�B�t�
y#��#<�@��X���	�%�9>�q�c��\�'��!��*�Q����9?Nk��9H�2��̠d/V�<�^k�>'�4vp�3+3cNF2Ns��5�B7���yZ�g��z������� x�h\�[Y����Q�?A^~�Q��*��T.�#���1�I溪a#�t�0���4�Z��jj���`��_�����I����#ͩVS�4��'s]6��H�� cc�'�>���X�����5rc.W�N�I���$�Q��=)�d�J ���C}N�H�TA�_δ� ���Y_�YX)L�5��]D��]bf���=q�3�]�hzl���R@ZL0Y�EI�*�S�ɦ�h�0M)�M� D���2g)*d��"������?h��nc������ ��j`]���������{V�L33K��݀ȍ��p3׷�y>�/ݙ�{9/zmiqg��%��eS��|=���$\���1=ϸ�����Guhd^H�ÿ��v:���h%�;� ���z��u[ӫͣ��!س3c'��}�֑G���
z�ϮRL�P�OQ�����p$ǘ@$�9�o�5������*�8o���y��9ć��Q�ׁ��)�0�q���?�x��k��&��������q�5�F-�؉%M�=��ii�M����]���@��?�z���w�=��~�[꓁�]1��E��?ʻ��2�P���Ø�t'���Y�Ӭ��{	>R8=:�={մ(�sy'�O����ܤ䏣�MF
'�kz$�D�YK@�rO_c�+6�,��n<澃�����h&Pc~
��U�K໽��e�s�>>��Һ�W���8�P���~�{��f�7� ]��Uǡ��A�]��I��v>b��}Ԟ�ڼ�Y�]��00��V4s4N���]yv5��)z�R��}-kp�bȉ�=� q��X��a_I�nia����x �qz�V{w�Ԃ��;cs����5�6��T��e������EpJ.S��)GC���uVX�F'�:s��s�D�Wށ�[Ԃ��z�
�>PI;X�y��H�=�դ]��pX�9Q����u� ��=�۶���9�;��w�D��)7m�@�#!G8����t��~v ��L� 1�L}Ozl��
Ē���Nv��s���@�"Y�;YF9�\���?�.�#��7`����� ?J���x
��av��I�?�`ս��cj{�����N~n(���� �� �Ӟ�O8�S�Y[��q�6A �t�NG=�M���hU�O��v@��1���9┟-c�`��9�H���x��r1n�2��� V �	�[��OZ�3��q�/��>��l
�GIj��?+s��r:��U�K�Vp�/s�<�pG_�-FS�<�K(6��l�,G+�s�8���LXm��G7�,� nNw�'��x�d�3�gz��p� ���rx:
�O�vͧ��H�`��2ѕ'8댌�Zѕ���ux3熎��� t�i�X\����nX�e�)�w=�׵\18�4�_S���]��IP���)�
� �dqڽG93�PG=)qZڅ�ޥ7�z���"�� �@����q��)A� �*�M�-A;�N�A�jV�9�D���7ϥ[�ҡ��Dj}�u��v����;�8ncw��XՆw8��Xצ9������[��ay����w^��jR�$�i
Q��a�/���b���y|�c�kM�X������������k���(� �@R����f����I#��g��Z�d�l����SD�աU�\� ���I烎��[H���'"�F}�,�}8��-�6v��8������I�
���q�?:|ҵ��^��r�a�����M1��h��`���)DD��F
�ϊ��P����=1�<���k��#2c��I=�=O�_/��U][U��D,�h>�g�Z����ų+�P�P01�� c����n�-��h�@	�p��<�ki$U��:f�~��L�bmYd��du��(�
�#�4R�v�BzW�(�+d$�Rdxc�d����Ǟ=�`Y�%��#�k�o\�2"y��
���{:{��� ��k�LZ� I��eL��zדZ����B���tD�Eyf�����׮�eii�<sč�Q�䑎�����{ه

&q׹k�ӛe�������F>��q7��|��]���tS�y�h��?�$q�\��kߵ��K!}�X|�����׃���-���� �W�B�2����]�ͬ]P�3�נ�0�O�nt��7P4*��|d�<�c\ irK?Q�ѸM�snLf6��5����9������#�ē)d  �G|c���Wc�Z6��1�\�����n�Ь%C��
�0S��c�	Ϡ4�,��>hވ�H r��L�J�Q�,ym�$��A�('��n�1�>�$;�7�P� �rx8�wg�c�Y�)�n�� �]��+��y�sWC31�3 �I`;NrA���X<�H�Y�,	H�OL��Jr�|h�v(e �e�:c$z�9�B�L΁Q�@�6zl��� ��,3��VG�H%���� #��@�D���V��$��d���� ���)`�b��g��!s�9�?���G��4�1��'���M:|�I"���0I(6���~��@�bI$iR&�[�lO'�C�{��5n#n�J�b�8%� ��FNܑ�:(�<�������T��2�Ĩdr{U��8�HJ0
�[$`����=@�*nU�m�i��u|���Cq��d�`�px�N?�p��;q-܋v� :J0G���Py���#��{{g�e��Т�f�]\c��N9��W�|a�͔�Z?,Q!��X�fbB�����UKY��괠���$Vˀ8>��g&C��	�HKI��W�y}J�;�Lb��ZB��\�LY�@�g8����x�@��D���
��w�B�C�~Z���E��S�9�]��b��V]�	_Q��4{/�,'Ҵ� &`�ob��`pr@���ޫ&�,@���z�9#�U���	9�+��,|g��_ƞP��!��\���ԓ��|ח'v��-A�!'k�drrr~��3K.�唃��Q�zUt*������s���Oέ�����=�s��%�sR~����*��l��s�?�:�Vژe'x��`t����f�a���) {�� ֩Э�RI�pz��s��F:���Ξ5��?\�V� �b@$�HϽ{�P�����9���k��G�δ�����>gp{~}+j2喦���<�^�ԭ=�D-݋F��=�V[w�F�A���A��+�Rg�����^�UB�NzW�_��gѠ{(���� ��Е�x^�u&�p�1�;/gP�����'�f��{��xX9�r�u ��&㶇~1��}Og��K(��ǒ�ʓ���}+�u{��jJ�p����<ν\����X�GYmR�!�� ��d����B���Fc4����h'��b>��p~&��\Yͭ�Ip�20���Њ﮶�|���~�3WfW/m�(��=ŉRIoe��ֺa'ts�JI�|�gP7�;U��E����;�����{	��h	��|��>���"��� ��۟�׭NjJ��jE�ٟ����N�.B��-�n3���Q�ʤKv}�D�p����?_�U�<�c�Y	;I��cw�V`}��w|��J��=q�8��a��D�*2�  _P1�yϹ�W!x���n�6�!�{�)�ׂ}�P�q$�i^[x*9ݒ��#�~uic>z�Ȏ���N9�q�>���eXF�G�ذ*�1�#$�����O~)�E�ѡ����;q��b���ǥXW9a"Y�� ��޽:欬�!����<��NW$��/9'��1Xm�3��UI�$,lw`���i��<c�kf��QY�1�+��?/���O^٩�-�(�c*g����$d�m��&���w4aHu%Fs��nx�<T�Z&Hb������V(����H>��;Vm�ݺ\\��*���m��� �O\qM��fh���-��� �~I��V���Y�"0�e6�ڼF#'��t�q�C]jRY9�=�&�6 v��;�<�9�WͿn�Ʃk��p���7�=k������"[�������(*O$��q�8�~[����g��m�9�g����j����\�$��f?�@˚��<�����ڽ�!�杀GJ~��v mx^_Y�A�2_��ڽU�u���t-�`U@NG �_��fx0�����R���0rF:9���[��Ky6���c?C��WI�-�p\��#��Z��&۸�C��*�k5A:�}�V�du�/�����@n��^�ֳArc�X�����9���l�Y'#�Ӽ���#o� Z�Oh1jq����� �q�8�{�ը|x��T�U���9>����Zi��Kc*����䑜����5*�Z&��;ݏ���̑7�� (�OBN� ���N��,T��=:q�*]���y'9���\cӚ��;�͆�9�������E��P�y9����>���'� newtarget)
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::iterator it = m_connected_slots.begin();
			typename connections_list::iterator itEnd = m_connected_slots.end();

			while(it != itEnd)
			{
				if((*it)->getdest() == oldtarget)
				{
					m_connected_slots.push_back((*it)->duplicate(newtarget));
				}

				++it;
			}
		}

	protected:
		connections_list m_connected_slots;
	};

	template<class  arg1_type, class  mt_policy>
	class  _signal_base1 : public _signal_base<mt_policy>
	{
	public:
		typedef std::list<_connection_base1<arg1_type, mt_policy> *>  connections_list;

		_signal_base1()
		{
			;
		}

		_signal_base1(const _signal_base1<arg1_type, mt_policy>& s)
			: _signal_base<mt_policy>(s)
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::const_iterator it = s.m_connected_slots.begin();
			typename connections_list::const_iterator itEnd = s.m_connected_slots.end();

			while(it != itEnd)
			{
				//(*it)->getdest()->signal_connect(this);
				m_connected_slots.push_back((*it)->clone());

				++it;
			}
		}

		void slot_duplicate(const has_slots<mt_policy>* oldtarget, has_slots<mt_policy>* newtarget)
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::iterator it = m_connected_slots.begin();
			typename connections_list::iterator itEnd = m_connected_slots.end();

			while(it != itEnd)
			{
				if((*it)->getdest() == oldtarget)
				{
					m_connected_slots.push_back((*it)->duplicate(newtarget));
				}

				++it;
			}
		}

		~_signal_base1()
		{
			disconnect_all();
		}

		void disconnect_all()
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::const_iterator it = m_connected_slots.begin();
			typename connections_list::const_iterator itEnd = m_connected_slots.end();

			while(it != itEnd)
			{
				//(*it)->getdest()->signal_disconnect(this);
				delete *it;

				++it;
			}

			m_connected_slots.erase(m_connected_slots.begin(), m_connected_slots.end());
		}

		void disconnect(has_slots<mt_policy>* pclass)
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::iterator it = m_connected_slots.begin();
			typename connections_list::iterator itEnd = m_connected_slots.end();

			while(it != itEnd)
			{
				if((*it)->getdest() == pclass)
				{
					delete *it;
					m_connected_slots.erase(it);
					//pclass->signal_disconnect(this);
					return;
				}

				++it;
			}
		}

		void slot_disconnect(has_slots<mt_policy>* pslot)
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::iterator it = m_connected_slots.begin();
			typename connections_list::iterator itEnd = m_connected_slots.end();

			while(it != itEnd)
			{
				typename connections_list::iterator itNext = it;
				++itNext;

				if((*it)->getdest() == pslot)
				{
					m_connected_slots.erase(it);
					//			delete *it;
				}

				it = itNext;
			}
		}


	protected:
		connections_list m_connected_slots;   
	};

	template<class  arg1_type, class  arg2_type, class  mt_policy>
	class  _signal_base2 : public _signal_base<mt_policy>
	{
	public:
		typedef std::list<_connection_base2<arg1_type, arg2_type, mt_policy> *>
			connections_list;

		_signal_base2()
		{
			;
		}

		_signal_base2(const _signal_base2<arg1_type, arg2_type, mt_policy>& s)
			: _signal_base<mt_policy>(s)
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::const_iterator it = s.m_connected_slots.begin();
			typename connections_list::const_iterator itEnd = s.m_connected_slots.end();

			while(it != itEnd)
			{
				//(*it)->getdest()->signal_connect(this);
				m_connected_slots.push_back((*it)->clone());

				++it;
			}
		}

		void slot_duplicate(const has_slots<mt_policy>* oldtarget, has_slots<mt_policy>* newtarget)
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::iterator it = m_connected_slots.begin();
			typename connections_list::iterator itEnd = m_connected_slots.end();

			while(it != itEnd)
			{
				if((*it)->getdest() == oldtarget)
				{
					m_connected_slots.push_back((*it)->duplicate(newtarget));
				}

				++it;
			}
		}

		~_signal_base2()
		{
			disconnect_all();
		}

		void disconnect_all()
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::const_iterator it = m_connected_slots.begin();
			typename connections_list::const_iterator itEnd = m_connected_slots.end();

			while(it != itEnd)
			{
				//(*it)->getdest()->signal_disconnect(this);
				delete *it;

				++it;
			}

			m_connected_slots.erase(m_connected_slots.begin(), m_connected_slots.end());
		}

		void disconnect(has_slots<mt_policy>* pclass)
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::iterator it = m_connected_slots.begin();
			typename connections_list::iterator itEnd = m_connected_slots.end();

			while(it != itEnd)
			{
				if((*it)->getdest() == pclass)
				{
					delete *it;
					m_connected_slots.erase(it);
					//pclass->signal_disconnect(this);
					return;
				}

				++it;
			}
		}

		void slot_disconnect(has_slots<mt_policy>* pslot)
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::iterator it = m_connected_slots.begin();
			typename connections_list::iterator itEnd = m_connected_slots.end();

			while(it != itEnd)
			{
				typename connections_list::iterator itNext = it;
				++itNext;

				if((*it)->getdest() == pslot)
				{
					m_connected_slots.erase(it);
					//			delete *it;
				}

				it = itNext;
			}
		}

	protected:
		connections_list m_connected_slots;   
	};

	template<class  arg1_type, class  arg2_type, class  arg3_type, class  mt_policy>
	class  _signal_base3 : public _signal_base<mt_policy>
	{
	public:
		typedef std::list<_connection_base3<arg1_type, arg2_type, arg3_type, mt_policy> *>
			connections_list;

		_signal_base3()
		{
			;
		}

		_signal_base3(const _signal_base3<arg1_type, arg2_type, arg3_type, mt_policy>& s)
			: _signal_base<mt_policy>(s)
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::const_iterator it = s.m_connected_slots.begin();
			typename connections_list::const_iterator itEnd = s.m_connected_slots.end();

			while(it != itEnd)
			{
				//(*it)->getdest()->signal_connect(this);
				m_connected_slots.push_back((*it)->clone());

				++it;
			}
		}

		void slot_duplicate(const has_slots<mt_policy>* oldtarget, has_slots<mt_policy>* newtarget)
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::iterator it = m_connected_slots.begin();
			typename connections_list::iterator itEnd = m_connected_slots.end();

			while(it != itEnd)
			{
				if((*it)->getdest() == oldtarget)
				{
					m_connected_slots.push_back((*it)->duplicate(newtarget));
				}

				++it;
			}
		}

		~_signal_base3()
		{
			disconnect_all();
		}

		void disconnect_all()
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::const_iterator it = m_connected_slots.begin();
			typename connections_list::const_iterator itEnd = m_connected_slots.end();

			while(it != itEnd)
			{
				//(*it)->getdest()->signal_disconnect(this);
				delete *it;

				++it;
			}

			m_connected_slots.erase(m_connected_slots.begin(), m_connected_slots.end());
		}

		void disconnect(has_slots<mt_policy>* pclass)
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::iterator it = m_connected_slots.begin();
			typename connections_list::iterator itEnd = m_connected_slots.end();

			while(it != itEnd)
			{
				if((*it)->getdest() == pclass)
				{
					delete *it;
					m_connected_slots.erase(it);
					//pclass->signal_disconnect(this);
					return;
				}

				++it;
			}
		}

		void slot_disconnect(has_slots<mt_policy>* pslot)
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::iterator it = m_connected_slots.begin();
			typename connections_list::iterator itEnd = m_connected_slots.end();

			while(it != itEnd)
			{
				typename connections_list::iterator itNext = it;
				++itNext;

				if((*it)->getdest() == pslot)
				{
					m_connected_slots.erase(it);
					//			delete *it;
				}

				it = itNext;
			}
		}

	protected:
		connections_list m_connected_slots;   
	};

	template<class  arg1_type, class  arg2_type, class  arg3_type, class  arg4_type, class  mt_policy>
	class  _signal_base4 : public _signal_base<mt_policy>
	{
	public:
		typedef std::list<_connection_base4<arg1_type, arg2_type, arg3_type,
			arg4_type, mt_policy> *>  connections_list;

		_signal_base4()
		{
			;
		}

		_signal_base4(const _signal_base4<arg1_type, arg2_type, arg3_type, arg4_type, mt_policy>& s)
			: _signal_base<mt_policy>(s)
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::const_iterator it = s.m_connected_slots.begin();
			typename connections_list::const_iterator itEnd = s.m_connected_slots.end();

			while(it != itEnd)
			{
				//(*it)->getdest()->signal_connect(this);
				m_connected_slots.push_back((*it)->clone());

				++it;
			}
		}

		void slot_duplicate(const has_slots<mt_policy>* oldtarget, has_slots<mt_policy>* newtarget)
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::iterator it = m_connected_slots.begin();
			typename connections_list::iterator itEnd = m_connected_slots.end();

			while(it != itEnd)
			{
				if((*it)->getdest() == oldtarget)
				{
					m_connected_slots.push_back((*it)->duplicate(newtarget));
				}

				++it;
			}
		}

		~_signal_base4()
		{
			disconnect_all();
		}

		void disconnect_all()
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::const_iterator it = m_connected_slots.begin();
			typename connections_list::const_iterator itEnd = m_connected_slots.end();

			while(it != itEnd)
			{
				//(*it)->getdest()->signal_disconnect(this);
				delete *it;

				++it;
			}

			m_connected_slots.erase(m_connected_slots.begin(), m_connected_slots.end());
		}

		void disconnect(has_slots<mt_policy>* pclass)
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::iterator it = m_connected_slots.begin();
			typename connections_list::iterator itEnd = m_connected_slots.end();

			while(it != itEnd)
			{
				if((*it)->getdest() == pclass)
				{
					delete *it;
					m_connected_slots.erase(it);
					//pclass->signal_disconnect(this);
					return;
				}

				++it;
			}
		}

		void slot_disconnect(has_slots<mt_policy>* pslot)
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::iterator it = m_connected_slots.begin();
			typename connections_list::iterator itEnd = m_connected_slots.end();

			while(it != itEnd)
			{
				typename connections_list::iterator itNext = it;
				++itNext;

				if((*it)->getdest() == pslot)
				{
					m_connected_slots.erase(it);
					//			delete *it;
				}

				it = itNext;
			}
		}

	protected:
		connections_list m_connected_slots;   
	};

	template<class  arg1_type, class  arg2_type, class  arg3_type, class  arg4_type,
	class  arg5_type, class  mt_policy>
	class  _signal_base5 : public _signal_base<mt_policy>
	{
	public:
		typedef std::list<_connection_base5<arg1_type, arg2_type, arg3_type,
			arg4_type, arg5_type, mt_policy> *>  connections_list;

		_signal_base5()
		{
			;
		}

		_signal_base5(const _signal_base5<arg1_type, arg2_type, arg3_type, arg4_type,
			arg5_type, mt_policy>& s)
			: _signal_base<mt_policy>(s)
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::const_iterator it = s.m_connected_slots.begin();
			typename connections_list::const_iterator itEnd = s.m_connected_slots.end();

			while(it != itEnd)
			{
				//(*it)->getdest()->signal_connect(this);
				m_connected_slots.push_back((*it)->clone());

				++it;
			}
		}

		void slot_duplicate(const has_slots<mt_policy>* oldtarget, has_slots<mt_policy>* newtarget)
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::iterator it = m_connected_slots.begin();
			typename connections_list::iterator itEnd = m_connected_slots.end();

			while(it != itEnd)
			{
				if((*it)->getdest() == oldtarget)
				{
					m_connected_slots.push_back((*it)->duplicate(newtarget));
				}

				++it;
			}
		}

		~_signal_base5()
		{
			disconnect_all();
		}

		void disconnect_all()
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::const_iterator it = m_connected_slots.begin();
			typename connections_list::const_iterator itEnd = m_connected_slots.end();

			while(it != itEnd)
			{
				//(*it)->getdest()->signal_disconnect(this);
				delete *it;

				++it;
			}

			m_connected_slots.erase(m_connected_slots.begin(), m_connected_slots.end());
		}

		void disconnect(has_slots<mt_policy>* pclass)
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::iterator it = m_connected_slots.begin();
			typename connections_list::iterator itEnd = m_connected_slots.end();

			while(it != itEnd)
			{
				if((*it)->getdest() == pclass)
				{
					delete *it;
					m_connected_slots.erase(it);
					//pclass->signal_disconnect(this);
					return;
				}

				++it;
			}
		}

		void slot_disconnect(has_slots<mt_policy>* pslot)
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::iterator it = m_connected_slots.begin();
			typename connections_list::iterator itEnd = m_connected_slots.end();

			while(it != itEnd)
			{
				typename connections_list::iterator itNext = it;
				++itNext;

				if((*it)->getdest() == pslot)
				{
					m_connected_slots.erase(it);
					//			delete *it;
				}

				it = itNext;
			}
		}

	protected:
		connections_list m_connected_slots;   
	};

	template<class  arg1_type, class  arg2_type, class  arg3_type, class  arg4_type,
	class  arg5_type, class  arg6_type, class  mt_policy>
	class  _signal_base6 : public _signal_base<mt_policy>
	{
	public:
		typedef std::list<_connection_base6<arg1_type, arg2_type, arg3_type, 
			arg4_type, arg5_type, arg6_type, mt_policy> *>  connections_list;

		_signal_base6()
		{
			;
		}

		_signal_base6(const _signal_base6<arg1_type, arg2_type, arg3_type, arg4_type,
			arg5_type, arg6_type, mt_policy>& s)
			: _signal_base<mt_policy>(s)
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::const_iterator it = s.m_connected_slots.begin();
			typename connections_list::const_iterator itEnd = s.m_connected_slots.end();

			while(it != itEnd)
			{
				//(*it)->getdest()->signal_connect(this);
				m_connected_slots.push_back((*it)->clone());

				++it;
			}
		}

		void slot_duplicate(const has_slots<mt_policy>* oldtarget, has_slots<mt_policy>* newtarget)
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::iterator it = m_connected_slots.begin();
			typename connections_list::iterator itEnd = m_connected_slots.end();

			while(it != itEnd)
			{
				if((*it)->getdest() == oldtarget)
				{
					m_connected_slots.push_back((*it)->duplicate(newtarget));
				}

				++it;
			}
		}

		~_signal_base6()
		{
			disconnect_all();
		}

		void disconnect_all()
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::const_iterator it = m_connected_slots.begin();
			typename connections_list::const_iterator itEnd = m_connected_slots.end();

			while(it != itEnd)
			{
				//(*it)->getdest()->signal_disconnect(this);
				delete *it;

				++it;
			}

			m_connected_slots.erase(m_connected_slots.begin(), m_connected_slots.end());
		}

		void disconnect(has_slots<mt_policy>* pclass)
		{
			lock_block<mt_policy> lock(this);
			typename connections_list::iterator it = m_connected_slots.begin();
			typename connections_list::iterator itEnd = m_connected_slots.end();

			while(it != itEnd)
			{
				if((*it)->getdest() == pclass)
				{
					delete *it;
					m_connected_slots.erase(it);
					//pclass->signal_disconnect(this);
					return;
				}

				++it;
			}
		}

		void slot_disconnect(has_slots<mt_policy>* pslot)
		{
			loc��vNoO��T]1S�`��g���nqؓK�d��i�<�t�29�Pד~g�WE�\�WQc��}ŷ��@�=��oB��B�sI��T�(mm����R�����ҷ�?��xX�#��<���K���c��{ 1=�=��qt3��}$>\���i(�%RBj	����`�:U�w�X�&|�����~��]!_�[�Wd���>c��͖�Q���>}�����!�|�U�m�FS��Xj��Y��`V����B?a������6�*�T�Ҥ���4��L��s1yZ�Ƌ�����,�s�e�S�*��	������,���N����%_�G����!F���Uw��y9��fq�~R5f�h��b���p��t4��{:�4Y?��ĚJ	2?�Ln�tU���_��p|q#��M�rJ�@@q�ώ�[E��5�W1�xS�q��׈�"���x% 
�����^�׻2���1F�%���Hpl���퉐��`��^؄t�^�*��C�+�	da���=4����C8����z����ᎄ�Q����<�B��͊ɥF�\�����!:���go#�KǗ��GC�9J|g���\ɇ2��c�܂��14�g ��� �s@6�!�R����}��>�����1��sy8�]���/���*k*`,�r��yC2����0��q,��#��G�B-�!C����A��n�1�H!4�x7h��?��þ?�m%����C8<���:��@���PV��T����m�hed����څ~:��l,_�n�Ѯ��S���S�UT��?8�D~r�ʯ}=�?��gM�G�vl�1u||�[멻�����v78�J�����%ڙ>Н�?���
w��}�^y�Lʳ��k%�]E%]��r�b��������u������;Q��o0�
�ӆk���DU��y7SF���Ԇ�I�`\�S/���ݕ5v W����DL·�;KgިĮ�$(�>2�B#,�oX7��ܫ��>��ޕ���x�+Y񕛟qm�
�K�������B9���?���&�H��I�<\D����k;�u��=�|6^h3�d��uD꩟ˠv� ��k�uH�[Ou�o���]���
7�n6/ۛ����[^��A&LN��@M@Eg���2�� :�P;�ɥ���a���&����D!U���K}'��S��W@|�0Y\��,}��
��D&rg�{z=�a���\a�m�Ω�P�|�-,c�x���O`u.]^�2���P^+��$)�������5cb�>v������>�8;�c�b����C.�-\@�m5�]Ï�VrB�ĿJ�%]��{ � ���0�xK�iA�?Z�"8]�1��{1���։8�ciޓ�P�&#���!�b8`��� ��Rػ����A#wS!K�I���}���2OȻ�1͋w�|�R��J���o����}'~�<��xԑ�$�U�?�'��b�慎�����u���T��s���N�c�:\�;�.qox��S��W�N�~���w���8&��@��{,��� �)�_ ���`N<��_�����c�R֬9@��2�Ձ�������$��"Y�����q@ښrgm�Q�?�!`̼lH��y�`4��ك�����Ԏ�v����_X!�+����gdddX{��3��TP�v�jL���������ԉ�Z����]������n~�ZԊ�G����6NxD`<�HW��u|�i�9�lkf�`Wi�O�@�5�m)MҴm����)l9��׳H5{hn
�V���������=����0s�*�\�}�.�>��e�6R%��#Qfٞ�|B��*.��	���㢜C�=�f��T5�Q���TZ)���"q��
��.r�g����� f�Ǿ����%�z	��9�K�����ϝu���R��$wY�=L�L���w�~GyI���~�&�����P��)^؏ND����hlp��!~�؃��s���Zj��*L���x��4�Mt��j�Q�U#Z.O߬;w��{=�l"����0[U��-yK����B㛥�V�[�}�)?dF�z)�ʫQlLƉ	?f�#D�Z�y�{�k���M�1E���+�y�'�v�DF�B��H���L�s ��P����R)�r�x>;Y�V6�� �u���]���e�*����+&���&�.fG�'v\��LcҵS�_�j�Wk|!��Ûk� ���7�,�jw&���=�(O�l�������k<�-�#y93�(�E8ԑ��Gc��
����~]7��ݺ���|��	��aO^�i��S��6��]��/ a���oM����qac}�?iw�8�e���>]����{���U����~�~=������4�%�<d+�=�ِ�J\����3!n[�-�u��f�O�;���ݝV�0O��B �����	^p��YhÇ�o�4
��z?\L*g��[kj�"$8�p�����5�m��Kǩ�p�����x��������@LuW�� 
s��1��=Q�ګ)� ďq�^ cɿ\E�E��EZ�Y\���n]��_~x�?&^,����-�N���n"�.8����Nt`ZPz�75��}�L�Qx��q�0�9BjJ ����x͛ȉ��f⿶�֣̗�����~�_��>{�MH�n :�Q�"�ȫ�DB/�t����ܴ1&	4i�Y�eX���ƶ ��/4e��FW����r�}� �8
��Y������W�w�h٠��῍�nbS����RT�+�a���zEQ���A�]�ՠ��C�:ҹ�C:-QW�W���J����)W=:ʾ�C
>| 6�M��(UKAІ��l��_K���Ɉxt<��2�<<鏧���W�N�R<�I�j<��l��1�}4��.H/O�d�>�2�e�R�;[h�����g�1�0�/�w�����H̳s%�6�cp���p܆�S^���(3M���/wj6�HΣn3�O��\�Y�q�'���*���$��a��c�E����yM�.y������7xܫ֪'�l��iW�
K"��*��Lcf�1&*� ]n��k���m�V��v�s����j��o�����TU�pf�'Omo��C?7~�h�Dmf���b�$��vn�)��!��b��~�L��}_����+��q3��zDO�+��5����Uo����/�?z ��0��/�T�/�QZPIΚ<L�}�3\tJ���F�ff�(/�2�w����$r��79~`������q����3Qy�eտ�	~�T]v"=e��x�ة}[ �{����x��(y�E�q��R0�C�H6ǰc��κ|1��g;�	Qz� �D�1�|^��R��(��ݬ��=��[`[!Ufb�.٥�����^�\!5�Ge�<��h
oW@���̶��	k��򘯆W���+�~�}��@���ߒt~)��R���GDN+��n��"l5r0�&Dk���W���І��dH��Pb.���+�f:��z���J�p)p`�B	�1�����[������ۀ�[�ck���߽�Y�_�|�k��&.�����8��"�W{�l��r���BD�X�߁�%EA$�!߁��<��v���g�;�~ �A󺃜{v� �?t�ԙUkP�＄�CR;klx,����h[P�,{�E�a���k�Pn@ t�C�qe�?�$+T�+�>I�N�`:�#tq�Q��:�����b�` 玎|��Š
�N<
�J��A��/��xU,B��Vq������s��EM?�B!�`��b.��T|�?�,���F���"Ly;���g	R� ��|97����c��"���1_�*�o���L�i?=����r>�k��w��&}g=A$)��lr��u`�sDVD��ɷ�f��ڨ%�^(ģN;Vzz��fsn�wu�f^�F�e���MvY8����w�$�7���>�2@��u�NZ��a��,d��{���%C�خ�n�9 ?��xQ!���&��G���	���@7�w�ܿ���/�ՆhSr��O��G�`�ڋ¯�&�q/��@��5��CV����,���^��a~;]�x�SAM�W!5��@���#SN��=��j����C���G�M�CRiIB/�i��1��F�� �>��Y���D�@H�W�_? v�W�j�v�jYW"ʸb�����Hr4�I�c[�j ������҃_�\Xt��=Xg�j
y���'ܛ/�����{�y�2��s�. �����~���1ų׊N�}��sknō\8��Q�k��/�^��E�r=�TfR��{�c�eM0�m�0r�B��|�'Әa�K�5�[\��ks�v�V�����Y4�'��$�E]~���즆���ڴ�� I]"�C�h��=��D�c皆O&=�ӟ�����p�F~������я4�#g�x�xq.˗L9��ib�������0ANTS:ʾk�Ya�Xl�`�\�;�G�^$�A���'�ǹX��.�����<!���f��,^QVH�qiV����n�Q����Jj2��o�S`�~`�-%F�&�czp4f``#�Wʼ��~��ɊH���N��$-z3���>�l����Z��_�4ţ�J28`1��;=����B�PP�q)\�����O�l�nO�
�L?�P����9,3 c��l�]�n=\��=���VʔL{k-�"��)��$�{'���F��^@9�DƐ�EQOhN��bs/|.��;m�	�([�h�����:��f�&
�g��&�E��L��iS��Å�6'��zA��>6o���A4+u��,��6���*��b�P{����!:����)��G�9液Bs����<��PK�rńH;��|�w��3�n���AI�����\ԉ�3ӻ�Es@
s<���<�֊x0ھ��T���{
�)�����87^ᱸ��X�噦r��cn��Z/��N��u�ϱ�	�{�c�I~�ݿ�Ff����J���r���c��!L[>���.͍�8_4'm2�F�R;{�ֆ�]*�
t�X1�	�������o�A�6{d��t������M�b�O�?��A`kk�YPfL_��PXoʂw3��.,h�&k���� ��oK��t�/���f��M��P�_jʈYZ:�����u��<�v6���~ƥ�N|g����Lж�b��`�)�v$"B�.�a�d�+u�+e��������ʳ�I+Fs�L��Ǐ����i�����+����G�9�����:i���=�5��Nf��ጴ7[�ڏ������˰����!o�Tä0��k��W�C�%t�eBV�nWa
�<�wn�=�=�?�_�+E+n*5G1=�#��`��5�a��$^"'�s�(p��6E�<N�y{�� ��S���x�R�-���,���9*��
�b
�&hg�<)[p��J�t0�'2y���(a�d�#��rmi���|��M��=e���?���_����T��:��2���x1�h�>�cʊѢ��0;,E��D31�
h01���Zd
ixi\�W���e��*��L�׀�u!3\�҈�K�q�%�¹�t�ɡP��I|o抅�����;��A&�M(6u����x��ߵ��5H��p왍��)!� =� <LG�Md$�2�U�%+���̏�DȚMCe�J:t����FC�Ş��ŀO'���	��܋�b��b�NO��b��Ά
�~�U�@Z���t��م�F���C���] �U��CC����"/5��i�F�~�*&?O`��+���|�jG3<4D�����}@����^�h�P{u��BI�����Ɋӆ?~���-��1��;�$"�:@'8��\�p}�����HH����Sx�i:�`���Y���2�#@���ӡƝ�]�{�,����1�]��B�.E�^��6��c����b��6����u�3x;�/�@�e�P��>-�l�Z��Zf��9������5ӱ��͇�����=���n�O0|A�w�c�,��\��`\��@y���H��� AK���W�ߥa��c�r��K��0�^kU�޷
���:�/������Ԇ��o�;K�n#���t#�r������ u���s�n�l<�PFӭ1 �M@3{�G�K�e͟��R��ڙ��g䭈-@ ԢZj�y@8P�"��r[�g_/���摐�fG��k�T8��N쉥Te�
mɬ �=}��������>��%(�N�JDW͔��}*�0P�EV�ߍ�����o���?��$z�R�tl��#�B�ǫ`��1����g��ٕ�qr���UǼ�(w�\�cG�q`�	�A!��$w��@V|Ծ%"���J9��/���ޏ����ـb���<��r<&�=ں�T�9��.��)�a��$�&�}m� u@	4��J��*d��߆}����綘���9�?�����G���冊׼?����g"�7�qc�Y�Izr�,|�R��Z�RɄ�^p3&|-7� �ѯ\$�Tm�F��뱪�-�P�b�vngaTmJ���F#H���-��k)�Ӂ�$/��Q��h���1cc>���B�A��|Q1��gk��<X��yI�K<� GZt��W<��JǛ�%�q+H'��n����@	J�8�u�x��/�
%n
�B��}U���!�c�a8$r1[ΐ�3�^�L#V�&��~<T�]�&�9�Hv��OD4^p;��z;��ە�,?��*�7��u�Ry�a����M��9K869�W�l��������(r�y����h���S�i�s,uLOM���*���&�bI���s�y���qd�e26�օ���^�� �V��N���&m��#�S�S�͡�!�����;zɔ����y:��g������`ko��\��񓮩~}�DE����3�t����	�j�h�z���w��@?�9��\M�ф6��d#��
?޺ٻP�v!�e��^��5_렉��=ڐ��)ܠ��wY�Z!o�c;w�=�b���O}�<[̡�u:W��~=��->e��ȷ���9��ُ���3�s���~�[�����f���)7ݵw����m�j���ߥ�^�a������Z�K�6R����o!����#�]������?|�	�ScO����YL8���	A�;F�<`d��ۖ��U�%�N�튏������i0'���6<��u���l/��7t��x�`|J�>��L�FrE0ɺ�ޯd8k�IB�I���uBだ�=oL�W��u��꘤ee]�

�݇�>J<;�r� s���]��3杰V���TyJM�����m��`L�T0>�B�vo��'��3�����S�0=k�����~0S>Ц_�g��r�&+p�:�Q�1T�G��!E2��ל'�0����0�W�sȿ7@�.�XS�!C��?�p��6�,0���-��/B<�K��G�e��V����yv5��I���d��ׯ^]��ꜰ������3����0�'3��?!GZ��p�}Q��b��%�.<}�6�!C�Ͷ�G����d���zB�zc�ci�vG�Ǘ�4�Wq��9�e-���I��B���ƙo�N�7Z�I��?A2F|\h��"�=޽1�֖8��q|0�0=B\sI�a�Q����9� -!�ĺ��Zd'af`�I&aP���ȥ>h�.���q�[3b��'
Id߻�h>m����5��{־������h�����~� �@������z���Jmz��(�u)>&r]��K�ñ\W�J��,Ut?d4��x��_&b���$�Q��p�,J)<�p��q>�X�� K���Q�
Y˲���ܺ�B�@���;�j�;��d=�Ԓ1��#@*)kP�db�I�~��3����ゃ�}���B�}�v�h���5��`���C]�&ie��Ե��W6`��?!C������Y�kp��II)��jߌ�l�i5���ZS8���;��oU=� C��((&��|y��j"?Z+�CB�xe���m���K�-
��"Ш����&��SMu�0ܨ�,.ԭR�Y})����R�OSN0�)5�+��[mme�1^��
f3���݈����E+�g+<3���Fc(AU�����W@�I0���_4^9��c>D�r0Aћ�ʹj 9ꐑ���5o/d`����jj]����<A�Xֿ2�=68��X�� �f����ԫ��������Og��ɕK�f�������.�v�Y6�� ��Qr3u<<�<'N��*��h�8�QO��6mJ�Y�)���
\��QaD��"ѱ1�'<��#�SfgS�k�f���p@��Úפ��1Ã�^4�-9=��f��xY���E�[�mʼ�n�"C[����L<��>�?_p&��i� �b����&Б�}.3�߭��f~q���AW�������-�\m��U���Jׅ�sP�	��K�w��dg;"x��p�,��k�{)��1�r��_o�0���sF���/Ҩ�1�����(�@��|j���]���A!sr�IW�*g�jX#�P]ʦ<�w�/�E�����3�������p�c�7�Dˠ�
_�<��|]�\Pvj�[;ڍ��q�ż)a��'8�NT�����a���_���v��ފ#��\�93�_uʺ�d���"��)�S���$i��a.��~����l�3W�6�t�Ӛ�BC#4+�������z��7X7�?������ t%���s$�P���@�,{���;�|�K���$���Y+����!�Z",5������>F�Y�xP��ݏ`{Ʉ�|�UV<1|�Ǚ~����J�dX�W��F:��e�ҡ:���Ĵ2�#�o ����7\g�&��~x�]]��\G���C�����b@@��ߛN��p��ވ��a������G���L��%zN���SkYO��z4����}��7�{m�[�_���y�U��4X�|4�D����*B~N}4��������{^����&���c.ڋ��8��(�6�!�X2�O3�B� �Yh��oibB�geQDnC�Tѐ),���/sN�/7iJ��/^r	��r˞�滮ί����'�{2��m];v�[�֟��,�EN��,����H��P���Lͥ��sed�ɪG���>�g/���9�ZE8zd��](�����ׅ׻y1��w�7����p8@E�	R��+3ּ��ΑB��r2�Լu�F��_��C梕�n΁7����_g��'Q���;���*�����'���{;�������A$���)|�)&{��<���*c)�j��-35Kb�����L�펽IG�Va�Y�oOD�~B;^��h�tϰ%ȌMĶ����8�N�ku��Q:S���i[��]s}�6x{�B�&����������������<Q.بP�y���GA[��7*M�4����q�`�?p@��ܽGDF�D03�2Y�Gⱊ�� �t�#�v�u�уj�P<�ce4�<��z+b����̇��xR���3PĶc��`����}G�
���k�TJ�0�)���\�~��h7�-����z*�Z���n൥E-�29i蛷�匌�w�A5�&k'����(A칩���/ZΆ��;@��5�r�=L�DWґ�W�b�	̊��F g?�g�kC�:ɠ�H�>v���%=B�܇:�F�v��
߳����p�������sJ��:�|s�N�P��nD1����G���o77���{|s�s9�Tز7���×JҽfG����Ԇ��$�8�cG����w�w4ˍ�7���+9F�u7܉��A5�٥H��0��Mp-�6wŘ#��I]V��{��$��t};�f��w�6�t�N�d�����v;X������2/EB�!�7f�jd�G����5/	��+{�{��%��ͱL��G��=����/�wu���@>�u&`���*�(@�\Z. I䖖P��{�Xcw��I�z���0z|�"�~Y�~TaϦ�8/S�6	�|����LJ���G��ͿX��d��쪗8�eƻ��5��	����'B,�����5�U6�.ρ��M�yb��<:�s�ݗ>���)ެrC�z���X����z��"S�*Ǭ
-['�Y+��w4&k�8�sDp�ͫ��~���S)������(1���p�����p�����,OY�={A��7�X��?�c#v��h�X�V�I������X��\ߜ���B��;�@Ah f�M������������e��g�G�ͨ:��Q���J��w?����G���^r���-t	��ț̸3Ŧ0>%�g3ĩ��3]��{���̡̓��xd�G�4N܀��Y ��l�I\�ƣ�\w�p��z�|��*r_�34��2�s5ˍ�G��^��H�^�q�-�8-�GC�.޼˗����!�*I:#�Y5���^�B����MP
!�=��Nj�S�/��0Ur�*�|� J�q(�S&f�L���w �Rڔŵ�e����k��,t�.����	;���'�K�囕��Gc<f���d�N��ؠ�������L�����Z�I�]=��M	�L��Z>(�A����"�Y�:|�WU�C���^�2;�Yǽ*F�%@����~�&���2y�q̊���|
�Ɠ�«D͈(�_�*s؟���Q������I=�Z�$���)�B��ڣ�@���R��%C.��<+i��B4y^d�
�.n`�=D��=~�����h�|u��<���Je{d׵�/9�����*芌/�H��ܧD��իB�2��a�23L� �	�'��5�2�~�}�J�]���F�pz�5D#�q�uWݠ���Y��N����Le�����d���e�S��QӲA�G��0�=y%w>�!�G�ğY�ϯ Z�~Obm��7���	2m�_���n����G�y__�\�A�Dő�މ�T�lg�W���t�w������.�ɢ���$�T�6�6}�>:�`�䀐�[��$~�t79K4��_$��}������1+��?��;%
�u��D��j�{�ԣ�O�k%Z�Prb��������j������]0;��*(7X���@�|4d��e٣�/��Ն���@��\"�)Eփƿ�s:���W�.�!ǭ
#�m��
z���>�����¦]���3u��ǹ1�����y� �C��EL�N@ԏ㩈�A�A�!�8ED�6��<J�����]�5���_5�J<�6Fc.Y��@�+$K�n(�����V�t?��)M�r �3�e:�O�x���܈���c5[�2װ�����	�GPp��t�k�
m��`~�Vl���s����qΪ;�e�'��&��ɩ Y��5��):T��k���P����-�;�;����!�{��AA�#Y,E�#=R�gP�V˷B�Y���,9��V�*��oG�_+�o\!���V�����~�4��c&�N����~h~��?�cߎ���8���}�����F���#�O�>3qa�4lt�� э>�~H�����"�|�z��H���*��N�Y����s[a�x}��q����wwF�)�qC�	9y�L&
�vBn����>��j~WT�W+�w�V5�{j%~�ѣp�L���\>�LS��!ߣ�/�k�6�o}��q�8���)��
W���&�%RA��`�.��� ���*9@OѾO��pb#~�J�D!��yT�X���Lm���%��D��M&q����P�޳��"�m'	3
}�d1W�Q'!^F6А������-.q58%�3��Qmx?,rx<J�����2����{�\�&����?G�	�5��?������le�8���e�]����x�8Rӑ%\�y7���]����B!�{�I�Q���nN���&���ɇ���#x	ߠ�x?�6�ⲹ61�͵8��9�Em ��!���2mh�K�-o��4`�8Ͽ$�@i�r��F ��bC ��*�<b9�6J4�H�sX��NoSf�C)t��  ���c���z%)<���{P<\RhS:�Q��K�m	��'V�K�h�l�Ft7M����o���lp./n'Cc[k�XT�L��%�gG*wf1پ��y�ug��
�cJd*���m@��}��s��JL/�u����Z���e۶m۶m۶m��Y�m۶m�}�yϟ�&��IU*���s���� N#N%�\2���K�m��o��՝!�Y=���ٞ2��G�ep����e�@�]�D���P�TD��s"�N��%Q2Mrm,�(�
`��w9W?���X4�59���#���qF̪?993h�����v����_#Z���s�t��M�nc+w�1z���L�t'��pcKX�<	8�"�Q5f�AQc�h��R�$��9���=����5�H���Ԅ�%���)z�<����#��Qf(���4$l���Qg>�~���P�8�L.���X0c�mn"T�&����Dr�F-��?�O�Z�ˬ�������\��L"t}ǯ�Ji*�!��A���"b�,_��[�`.��������T����h��k}y#P)�+X��\L�H��+{�	s�a�b��X�mq�axAK)[��hwR�T'�l�JBl�dB�|��.������q�6�������tjfy;��N;찃��ϋ^^�f[fyE��&����b�1����������$����>8�*�5C0��<��4��$Tޏ�`�����������1�9$�iT6��WѤ� �yKx!SUq!@G:��J���YG<d`���P��-��[�e0��qN�J� l���q^���^�Xt��Ck(��S��d�yc+��K�f��"0W��o�\>��~�{��\���}���e�t�q{�F?�4g�7?��[U�:�����|�ȫ���s��~O�:���qEH��=�=X��'Xn�o�E�bsͦf�'D���k�aF�_����]|H	��]ʻ��jW�>f�6��w��qQ��[a�#�UY��k͡:��U�6r?��9$� C���v�5,�E�M�_[��g[�v����{WCX�0�~��ƀL�&\ ������s���T:�2�	�ye�q�ec��~�3:ir`�i�>.������1���2mww����l��W��D)sk��4x��<�7+�u�CSjO�+7�Ȱ4���m��::7*���=t��s3H�Ӥ�s���k��Ɯ&ōw@^:�б�m�4�؀6Y �qβ�e�m��Ê5��K��.��搽�u{tWur�(w%/cc֚)��5��DVcO�M ���]�D0Z�sM�>GD��U�`�z�	��
"��%���L~���:��>�j������������������4��D���5�;��[���W s-���_�F��j{U�Ǧt;�H�!&G� ]���ؼ�=���i�����]�o����cX�dC�f�G�;�Ƚ��qG��q�&�i{#"R�K��{���3�L��S�Vi'�:U��s.B�!���E����=��Y.��Ě���5{f�K�;n�;����m�kq+�����#/�<�sFq�����/�z�e��ɻ���6��!�8� ?ƞz�F#�)9�gX��[n�ks��`~�4՚�9��}c���-��MZw+D1Gjj�{�ݖq�@TS�]Ne���8?4�`9��˺�$����	.�CQ�R��b�v�����t�;���8�}�}�,�3�5�`���b@C����g���ԟ���bN�v��@e}�Ӫ�ζq}�\�X�MRŘ�V.��r�gtg�F����S7>\��Q?�`c(�N� }�����E0�E�����9����4��U]$��KR�L��s�8r�+��<@�Y��wǰ) ����N�W�ehgu�Ts�ME����"kiHe!*�~��h�ZI�6�2;B�3�d}��&��6&~�����K� ���N���S��Q.;�dz�M}�gU�`RcY[r�I$��=�J��� ۘ�Θab�2��ʗ��AB�-��s	l���t�I��ʃ�F&!ꕽ����k�V�)к1{��|��I��M!�8|�Y��&)Q�`��NqUp���������v����O�*5�Iճuj�\a�a��ge�yg
b�K��&�il'{_
�Kjq�g�^�/�\��Rt���9u�ؾ�́�"����b��T�|�;c�>-�:����]�u7�*�["\����U}�����a�ĘT��8�{Gʬs�x\a.;����"�Ah4ی�3כG��D�T��Ə��U8+��vMɀ�9�&�72	v9�jׂ��&��#]hG��fA[��RC�Ǳ�e�r�n�*�D� �h1yU����6����)����{�%��f�	�@VB������΄����3x0�Mr�`\���rG���F����B�`{M�
�<�k�-[e�هZM&����A'Vj�l�C*	_��OƲ�:�ԍ%���VCzuXGf���#S��ۤ�):5t���C������4����픧/e��G<�!n��&vJ�Q�JG�̡����<:`a���R�H-��J��S]G��0��^<&й�pQƇ>��ث\��\�4>��R��u����54���c@��jٱcj{ʽB��9�Q�==�S�4���:Z�=�{�\�g�g���s��9O�/錣�?��{�d��hQ�P�j��9k�_eVt��r.1N�D�aǿ0۔���$���e��:��ԿQ"&�:{>�����p�w�.F�E9�)}��َ�!��h�Y�7ڂ����%��i�G�C&$,Ǉ�I�6�.��
7���Dh=Tͮ<,��O�*fy�i�efPjf[���L��B���I�Təs؈o;8�M�arw��t&N���rm��*�S#�8�⛴T�d[�t���Lxp,�K[�*+m���� �<f�(B���F�ݨ0���lU5*�ޢMb�������Wbl�/9z�F21���&t�hdf|�Ӡ�#�g���[ĕr�N�#Adˈ��B���!�ɰK#'�,TF"�N���gl�:��
x��`%D,V��r$��]�m( 7L�Z�V���G�����j��;,X��E�1ܔ������tn�Q;��Y<A�4}jmPf���B�1j�;Y�ճlb�¥�YrM�Zm��{,��kb(�d�2]K�@��#/�e�0�|j�2�x��&Elo�A���4���	-E�K�k=�cF�f�
T���3t`@O����F�!�:�
l�N,}�������u�3�oh1X�5��l���i��o|G�I�%��c���0S�6ݹ���^(����;8p�?Y=�јT6i��D�e9|1|Fr��f�=��g/h�#L�z����/������MZZe�+X<�J���GJ�j4�wX%��3��,�����2=��6)%	��]7��	{�A�]
'�L�EG��2�K7�M�V��M��2�+�Y�����
XH*�c�v�o�����5->ߝ����f�2�J�m�"~��8cp^W��&o੡�oe#��\5ʴ���vs�dΊ��̵��8�r�݋{H�"(R�F+��emך�!�JX{����Ėn�8FHZ8W��1�d�Yެ���MdF�Πs�lq�F<L�spx�ɲa)�^,�v��!+fB7���T�`u�������^�pyK�!99��*��\h>>kp��r\����c'�yU\��XkH�f��^!��SGD��κ�sY����&g�K�s��2Q�������I���6v,�ܨ_�,�*t���[t�בv�����ƲI����)���C���{*�0^���;
�ہ6;���ΉJP��Ail��^���<��fP���-|_7`�a� 6`cLJd&1��H���cB%#�xJ�Ff���"*I��J{)�r�oB:���鏷˶N�Km�0��u�S��\�b1��l��@���!.����j�Bm.
����3�X}_��^[��Ɯab3��b�T;��pz"&�d�\N�51��H%�`��e�&jn��7�M��_��
q`�u���y�;�[��9Ŵ��ݬ~.�v6k�1s�3
c*�L��m�ʡ�H(x��.@�e.�\Q�Md�| B=DLe��m�NAčn�&�/i��L�� �V��V�&b�?�#���׌و�B��&1T��R�$s���+e�C �W˷oq��<�D����5�e�򮄙v<���`!(9�1��Ƒ�f�=W'Gnn�`7At�"^+v�ȣ���I�>��ʺ���nL��7,I^�V�~����Yb����<^�/O:O^�kr*f��<8WǃG}�$��B㼵A�s�%9d��a�oiu�"�5hMP.�8 V�L$)���Yi)Ǥ��qd9��T#ޢFB9șQ�qꇀ�T���"�#�c]zz3\�~U����j��s��$���5�I�3����V���q+u4jZo]��O�[lU�De�-��β��s9���f'B�G99C u�`�7��NK[y��dxr���W}�
+߫.���^���Q�`b4L%5}�&�`,G�g��Z��jH:R�XW~��yLJ���n�.���@p���B��#%�!������r��B#Oh�˾�DǬ�^���Z��swN%5 ������7�oQ(�Y�f�
����V%��@=�e�Ў����b���k�>f��֐�wJ�g-k2^�p�t30�E<�Vی�S���|;o2u�5���	4}vk��RO�hK����a��s�^�(�=�v�[
G��rL�f/���;̄`�ʃK�""C2<  ���3=b�أ��[D��XbV� ֔x��b>1*=<.�1z��BE�d����|�C�`Z��tu�ho�nNϦ/P�'���\�ٝ6C6[9&W�K�S�m�}޶7�GG��p�d�=��K.�������b������X�n�դ ��,��n)�x|Z-8�.sN��pm�@�糙�����I�G������YV�r�A��������dN�����<��o�	؟��AE13r5B4��+�f����.�^��!VI%���iIƻ�9V�f[&0��Ѵ�s�X\�jJ �ř�Ċyv�Q��e?4bvr�E�]����˪�|�P%^�0W�=����i���3�.�z'��,D�ޟH	Pp�3Y���$��hmX���Hx��=c�����#��To�lh,q��[[ʁ��:O$�y�i�E��K��P�������P�t,�xp��uy��B��R���.03߻;�	(���M왲0�����p�&���Pa�P1�+�C>�wur���s�;!���aJ���tt�OS�`�鹘y�#�yh�^�ܗ����+
�&g�c7�p����Qq��R�jY4L�\��*w1y�P��nAL�Nd���	�˫I����5d��c��c��1�a��7�`�m�1n"��/, F�HWQ�۝���݅�2&�biM��� DT/F�&N�%���$")�јE�`L%�ny-G��\:I�U��j�Ib[�F�#!�EB.�������A]e1Q>^6
;_s7���|1�!8&GDB���)�Y�����A<`G�!��)�8o^���.�m����y-�`,x�(���U���"t�f�K���q>����Q�K��(��� l�r��`S��T�g�-`��FG;0O��t�pc�,-�rk��e�S�}{�n�0ۘZ@�
e��S���d�Kz���ٞ
>}1�|�b����e�M~���4���)?|s�Ӻ��������l~�N�=�_��{���✳��
K��=i��}2ș���9h����t翹҆ػb��Qnm#�$�j��:B���p$�Ni�{<��,;6B�b3#gPv��-;,���YJX��ã��s��Wvf0K-RZ���=4�!��ec�$h,���Jw��/�������uB�&Y����X��V�u�YwUj&���JD�~Gz�|���;�i��ˢ%��l4�ų;S}%^�f�<���ox����h��Ͷg����Aw�u�]Y.Gi7���U.sP�����F���-0%P�I� �Z�ʁ�!W��� �8�cs# ��q]B��9�}��gOpfL��w�&�=�{s/s.i7�����Tjb �!�a�n�;���5a<��hH�2ݗӷ�ij�d6�aԊy@�h��%�/��Å�M�!��9π}���*�s�֚�b�7_J^��D6��x[���l��&~��R����p��J`��u1ߞ��왛c+������J��y���Ȳ�J��YG�l
�P:)4��s{����7R���w������u91���9B�>S#��pH:��j)^4Wn7��IOƹ�5���ͽ�rv�gn��W_�H�Y��?Ը�1OwB�Z)W4||����l�z�^m{�����In��A��ܓ�/���1q^1u���h�Mv9�@��x�Q:܇�t&�^���Y��ʂ��K\0��������$�"q>��%��	C�^K��Ҏ�'b��T�� -�x�s��&E�bH�����H8J��8�_L;��-�g��J_�7��.X����Q!6&���	|9e����5�I8�$%J�
����Řbfp�*%�(!�9`�pj_i~bR�5:��:B�2��ݜ����l��%]���̞��I�����
�;f<㐘v�P3��vi�c��[y��B�����`��1B�&�~BBdǤ�x��Jm��փ�u�� �
f��:{��H�G����-,'1���7-�u�����z6�lB��$Q��
53��k�D�sP&�Ho�]�P7LT#�
PT�����X8<���u#�z�����d?��{'G��h��	��A.���6X�l�	�EһX�4�XO�ge(jk�]M��Պ�-
oC��ߋ�4|Y9��B�@W#�[
�v����?�w3qٓ�9�Q`���tG�(��M�+�(���d����j=�@0�����5~_h�ږȪK��{�����1Kgy�>��=C�x`�x��ђ
���I�*�aY���u
s�E��L����ԁB,��lL<<h���l3tز~�7�y��K6�l�؉��{ �<V`�Y���ٺ�䖭O�N�`P���X�+���ŗŸ����M�]��o�Sa��{X�`���h�Lk�{�M=��=�J�W=N�5�i��s.5f��ݢ����K�=o]�*�ss�n�@����a
�U�9��c3�rA�N4�,?�XM�a�������0�x\��Nc���/,:5�&1�� "t����:�� H;L��4�l�|xk�Ε����s���8"�� �cylb����;�nU�7�-�c)���&��J�,����ͦ�=p�{nb��f����-WN:�Ix>,��ޜ9�	�$%+�J�3y(��.�sM�O�ʎG�1���,�e���R0��eK��Y:�R����z�Ra��F,�⥫;D3g�j��,ڤ<̑T�Aq�ciC8��"��,`V�"�D�g�K.Klw1?ԦȤ~ ���,��Ta�n�Gb��*���wz7l��3p��&X8�nH���-r9л��n��q���4����}B�`!�P�$�Iڎ�x:�!�*�k���1��|�s2bZ�R�u�G�y��f�o�Cc�����6|X�/�ɰ��v��M;�Ff��Kq�h��i�y���x���g���KtOZ"xQ:�h���<
�g�}��TfI�����8��\&��ۑ�	d"�	�J́���qP��2t:��Cy�܆#xqi���,tqٱ�a���lr�(�a�i����5��)((��&Ӭ�Q���̐tēr�X�y�Z��+�64+Y�dx��P5��o>,���L�O)���J�"}�s�a�FХ�h��=Yj	=R�X7s��(c��t�=�>�u��;4�29���}Ѳ��fVn�^Z�%v��� ��d܀��Ą����J���	���\���m�^��k����-�(���;	Sb�9oĶ�]tؖ��Ns�x�̮��l���bԜ����bZtx��K
�_C���j�l���I}2ԝ��q��Ʈ��!ϱ�Ҵv��SǮh�� ���ɗAw���H�ɀ[b�-&o�9<� ��7h`u~�!o�;�&��h���ݒ��%$"��A^l���?&�̘��p��I�y� ~�	'w4��8BAHJV���2��f4ι�LB��0Y�{C�c��Mdt�Wk*�fE���V,>���G�;5�hO5��O��[�k��[(�2��N��\�'$I����C,@�/����M��h�5M ��,����������^�Mz<���Ā~G���"L#��zE����
���ԅ�҂H�#`��8�B�v��x�JPs(),�7m\i��0#L�X'K��wJ\���[�y�\�~)�����+c�}�b��#�N!�,-{��k�$�.#"�?9�Lm�R�&"�MZ�IDM��ғ�CBz+�U�,+p逧�Jk*�a{C��>���K����蛼;~�4�-s搴ɪ ;zx�4a%�8�K�'�;�F��Q��s��hܺ���^.���Zl�S.��VJ��mҨ�W36W�چX�`���̓˷,�I^Xc"|J�mx[K���CӍuظ��@Ԥ�f��	[���"z�Ϊ�n�VBȁ4�����r�搉�ѓ*�Լ��u�ٗ�v8��|��wotV	*I)N�p�ݻ���\��� ���(1��m]r8Қ���^�Y��q�SA�#)V�a8�)/��=�ǺE����7�x0����Jjp�H� ��z��$�=��v�5,������9��:_r9����>�2������)�!GKӘO��Szf�Y��9u�d�+��l,&����Ƨ��z����Aum�w�#s�(��*>^W%p�D�����^�ذ�W��3o7��#��
��d��XzN����9iP�="7D�C����H�<QR�L�������ՋL<_�K�3�]X;�8Jd@7N�P��M���U�+K�Pݢ#䫺j�YiR�8�l�c4���|g^�T���oA��.�;��,f���.WjٖRF28Y��w�M�2� k�˾%aTN���fm8����:���EYI$L�:�E|��L�԰�Ih]+�wE��06�Q��M�nji��v�V��C���gx�cCU�`x�[E� ��.�W�P��q^q��f����#G&&7hW��|@�����ȏ×V�(�K�GAyHW)ϩ��ot[�rC�r.�E;����J���֏�ω�#���V��J%#��
rx���3�O�PwӲJ�C<���hb.���,9��nh���8F�pt�|7�U�h"�X;#��O�da�v�V��臇��$�� -��_��+�^��GH<R���Wf�Oxa���ܹ+�j�>�\�BQ���ڮYK"9v>���Ba��P�4�_�z�b��w�l�������q7.�S�0a���?|S���l<O;����Z���`.N՜iYpˤG4v�:���B8O���l#$�Fo���{<'�P����ƻۏ���J�aٶUٲ��d]\� bgļY�6h��bB<��3����:ζ�h%m���Qu��,��-�MG�Ԑ���RAE�.(x�q:s��I��Hqr�@9���J�~XE;�k}!��%���U¸c����
|OLH�MD?䊛��2�r�7z����gҵ��^0���r��d��$���'ek(����	�b���@ʢ��w�@�a�i�_��� 򕱈���]b㏺R��C�\�s4$-�*P!̙��D���ǝ�p�3�N��%c���d�H����H���L�C�O�\Pb&t`�$��h/�`��xT5���@���0,h+�i��jNsʁ�|eX8[o��X�]�6h0�]��|}����Y�� st�k J�c��>֌��nV����L#���t��MrH��i°�s���M-�;Ժѫc�4bd>0<"<�E��_���Pwiw�1�C��G+SUv��-���g8��h���═]���E�Q�qxϮ�uŨg ���x/���!$�������21���b�A��+a�p��W�ڨ�d���������ۓk�!D�6�%��פq�X�se�3�L�4h��aB˸xx�j��S�8 �0�+��!�*�S�"��Cl+'�d�o�� @��I�� ��zn)�TCZ����@�j5f�5���d�P (�������ܪl� PqV���r�R[������;3����K@��L��$��Y�h�PiS�[C5P�T���URk7u�����-miK�[�a��|K"�G]�V�w���U�Y�f̮'���XyGe	�gb��M�<8�k'O��;�����Z�ONB�x�U�F�����F�v�kJ=��GW�jL��D��1������%�e�n-��x뵥�Rm�77��Khc�/���I�.�F@6�w��KM�����	�d�X�X��$=�x�����ɚ�צklSP�7ni-!!���W?�8`Ȣ�z��`��o�����U��XkWc���P,���M��U��j�O]1�O��ó�:�T�dM�����>C8�\QC����|�Z���l�`]c��� C�%��ħ�+Q�x�5p��7�17w�b�*��p��̂V{	+��I���c�v��a�4#<V��@ڜ3oڸ~��͛0���`Q��	`:�a�,���s�?@�ɭ��|���ҫ�ߵz��[D���&�j h�w}���[�@�f��b�P���� � k""n��TV��G��Ѵ>�<�Bh����$��s��i�
�  (߲��ʎ�2"�-�  h4P����\yVA��r�pq�\�S����2�q)��#�Ҫ�T7"�!o��Dm5Wv�R�����|z�J�R�T��呡��l�[�s����V�kY�_;��e;lW_u�}�oz}kF�K�(��ޫ�oa#�Z]�e���Oo�ף���mA�z�A��������{�;H؊G*8_-��H뤷��G�5��5_?λ�+�O�D���2�Ϧ_5�[O+�����6\��I4�Z	K�c˧����b5	���[�?���
��G�p�������t��蚏r� �a|��j��LȲT)3(+���+�#9�ɗh���<
Ų������q�;���
��ب���f]�z��^l��2:��r-9�|o{��3�-$�kVg�8���^�m��o�-s�E���.�oy�Y��5L	��{L�R�:t2�����N�HLΟ	XT���_�:
�rn����ڲ��2b��q�����.\��<t2��D �_�lƨ� p��9�A�ʆ5_�d�Ƥ�8���[
 i���M�b�2��[Y�5�Y��15�ƚ �|>�X�Mr��>�l��2����ֲY ��Y3���d��[�� X��2LZ��i���u/�5����=X����Ű��7�e>g���f�Y�������s�pf��v���v��v��0a6����n
����������|�R�Kn?�aI�F�E]��J��Ld��c�]����<3��ukCv������o��/#���5&e�np�bp��ikn�j~�@��FT����h`��7F��,����QN��s`���e��YLL�Cg����愒��<���Y��l�b�vᏗm�i"��p����jsTN��t��;Ԑ�k���m�T�?���bE%-�T�5�����>�	0�c�>������cUk�x�p_-��A�>22
����G��Nm�a�l��o?�2���R���@CÂ�	�(7$=Gc�9�l{F55�̀��_�N�?��@��5�}#�y��ڞ�h�π�J�.�Z� #"�0�&ٞ�"�S[�I�Ȭ��>�.瓥��j�g��ݒvڽ��L�ߪSՁX�Y˯��g��0��xt�{��JKq�2�����h���*]s	��ý�9ܡg�X3�'�O-�[�����SYE6�;ڹ�s��q冧G��D�ܢ0��9�+�fAk�;��7�Fo���7Ͳ��Ư�t̖.Ő� �q<:ЃN�*E�-J홙�B��p���j F�sF�A�US2�=�!�E�}����a���fuduP�~�UZ���9�Lr�k��h�a��l)j �$rG�n������q�e��)��V�"��r���W�ͳg��a��N������L��c�����ϐ�'.�v���<�L�ظ>�����Q'	�9O�<W�`� ��x{@-�a������%���	�b[�㘀b��b|�5���M.s��z��1�� s�"���q�����������,�(� �`li{=��H��Ҙ�tK��Y�Xp:�5y9�ݙI�L�=�@�ȵR�
�CL�P
�3�/����\��h.(9騨<�|�IQG�l���74c���ھ�0�d_b��Q�f��#�x�i
�	[tcaF�������V�{��_�7��ˉ��-p-!�
m��CAY-����%6ui��R��3o�!㵑�
����-*�M�"�^I�Q�5Bၺ�����jB+oo�Q�l�eR�rΗ�c4B_����6��/Է���k(���r:X?I��NAe�O�#;l�K�כ�����z��z�Į�ў��m�~�:Iq��dP�D↫�O��o�붭{5=�P�(���t�*�@	�YA�Ŵ3C���jyF�5�����/5�TO���<"A'GL����:ld�Q�jB����'�(#6�R�f� 2W�+d� ��TV7`��S�u`A����@�t��6�U���J��* ����'3��3�����7e�	5m�k>&MW%��5q���2����}�i�l#�������?���k�د�y��䫢:�ޚ���7�`�ڝ��S_�X�|����/_��]�U�L8�>nbI�Ӿ�0j�L�b�E�)��MN�"�W&e�ov�����WU�����x������h�/�1Y���b�+U�i��ʽ}k3̝Ź����"�����۴-*P�W�ɿsP��)�)64h�'bCx�YO�|8qZ���:s,ϮC�	쏕�/�=���t�ފ#s̰�;msߔ��S������ИT��N���ѹ�i#�d�v�Z�I�Yn�-����^�*�*Peb���_�X33�S�hd�?�ҡn��ؖp��ݙ���l۹�S���\ѝR�����I�<�����b"�%7p+��1��߅n�"].� 1|�Y���V���ĥ�N����G:S�p�y�J��Or��@�S;/�>�UR�jc�P�Ѿc����@<v�}��Ϲ��0�/���e�k�����K����y���b$z�Z�*�88E���,��a�%�>�?�����ul�k��~��6���<��N�l��Sa���đ=w|� l=)G_ה�u���Y�},w����Ů�xV��Z��f^��/}~h��%��1�uY��Wy{C���i�����'s�β�DEL��	�tN�O��%ު>��wn�|���Z8amwsH\�-ou5���{�ܑPo����DOV�X���E$&�x��O�:_w��v��vx��,�P��E ۷�@X�b
����IP� [�/1�y"�石���0�r"�^������宮b�ՠ�Al���n��$2]}9��f�0�8ͺ�d6�F��Kg�P,���F�P�����2��\��-�+������X��ެt��?p����Xv��\x��	��+�(a�jl��fZ ��`��,pN��h(G��]�����j�8?�Kg�s��2�����w#o�u5O�@�o�`���F2�-bV�.3�"��X�A�]j���[{���# ��%6⑎,�>���Q	>5�Z)�`�ɇ��讦d�H�6Z�}[ڈC_��G���d�z�w�<;�}���+F�`#��`��&�@E:o����U�@-����\4�M��~�t�7R\J׸r����qR���d���j��y�K->���WD����[�Jm��jz̛��h�/�D��˄��}�wǘt��~�qln�ܮ8��!�)w<jM�7��F���ą�#�"�%�	;��qQ���\_��ŉA>*�5��#4�Rd��G�{���\�ٵa&a	��y}pc����:�����2������kB��=�J�>�t��hqy���ToL��
�0b�M	ƍ0m0&;QZ�:;ܤ����	DUـ�EgB�F��¬��@�� Aެ�5�bJK<
g�,uR3R���GKJJd�A����9c��i{-���_��ۺ�}��]	��nM�;?��o���J���9��C:�� �9viK�`���F&Tc-35��N�<`�8H����Ik��r�<�I1�$g�77e�l�8��i��}4�-N��?S������^Pt>�����X?���"�`�Q��4�y�j�.�q�}�I�Y���OwC�!̿�(���x��~�{k�W7�w]���C�.D1G�Hy���P����b  �����`�n)�Іz퀺�
_6Ԡ���4�����Y�(J-@��@Q�vPh��q�70��P����xo�O�~ZG]נ�oJ[k�Ь��)n�Q�Lj�t�h���7�{m���ǜavv�Ts�\�^���\��E�ת�)��(�\�[D�ʙ\�Ŋ�blm�Kݢ��w�)n#/��'��Y��!� ��j+x_) � K�l�꨼�����5u���R�-+h���[�Y���c�ͬ�`�U1��'M �%�m>4LBS��izk.2|�"�a��
6�+m�2�A��������f��h�Q�$nB�o���&�h}	�cm�ģw�oF;'�L�g*���4i��j�����VJ����*D֑]����(���v��yP����K���jŚ7~O�Þ0�C-�9���u�?���.��/��
�h/i~��,J�W��! ´j�:��R�u��{Ǚ��A�t$����`|)Y��93�*_��Ž�@}��a~��J�NSg��/1�ר�:lʴ.�K{�V�����J�:.�Y5�A4(�I�f�%����[�Wv��-*X�mp�m����X���Τq�X�W��=U�0&�Q�����VxT��iqJdeU���5��V:s�Sݷ&�nCo���������ojm�ԇ����(grZq�s:L��j��T��ZY3^��O�[6-9��C��`�-*���.�t�HDby|�>�tf��H��4o�ΚXl�����=�z�0|H^�����b��jM�j����0V�ډY��Z���2�f��M{:�N��0���*�5M7��[M1��!w5����4�3(��I��n�WB�E��(�`���l�k�e�d)�_�E���ӷ�����hX4�j�[���M�LJD�FQS�Z�F��jǘ3���I��0�J�pb�#O����3IҔ�f=.�Qe��0������=���R4&���/O�G}�%3}ϛ�΁�IS���X��(��H�4)%m�?�q�@�{�wJo�jQkBc� �;�̚�R��@s���8\ H���a�u�O��Qh�5���U��=��&�^}�琳�5F&˲�7�Q���&=�&u�G��$�$���M��%�L��t5���\MM��M�D��&--vT���9|O�E34�m5�����b�D�h�j�֤^�p�Q�ڴE	̓A�)��_��=hw��^���ʮ?y�������'�r��ʨ�k��;�Y*�h�.x.�4�V�S�	���5�A���5�V�+@�1܍�&|JW�����D�V׹݅�W���������l�z/�3�{���̕j��m�Ȥ1��Ԟ��hJ���g���ԯ#�-1A�n-������ٹ����|��L�d�uYi��GHMV�S��ˮ��AGwhNjcS-���h��؝U��1"��:�A��ۤ[�-j��9q桵��9O�
�$����t��)�m���.�Z:��
��@k �K�):�C�x2�^�A���z�C軙�:R˺�q^��2G���tbvf~c��ZI����?F�_�k|g�A�;N7 }N�&9xs���b��i{.���Q����Z[A,vN�{�W ����Ժ�rB��q}�Jm�5����.��$M1z�����2BSӚk�V�0�&,^�7�=կ��\Θ%e�7�'V�t�[��V�8� ��F�-�ga�n�sGݸ�������5��wQG�G��4�*�Z�'�9�H	�6-^uI.^Y���v&�k�Y_X�8��i�q����Ǒ������_$Q'4�j}/8�����ֲ���\g���d��M?<7�����������Zs����dg�=�]#aKɍJLIdKz�S�`�#�[m|�A=��r�P�5�jm�I��
��h��MĻN�n��h�,ZD=�8����<Z�5��KV��=�k���	B�a_�Zڔ����G�k�^�?�D<�I��떆C!�hiu	S��F��Ԓi����&&᪋���dh�џ��y�N�'A$�V�9�&�ߜ S�)JZ4�t�\Y3�y�N��� )�Pc��4J6�k�7�L�&������f��M���3�X���yvj���"�Ŧǒϗ]}�|n1�Aaģ�[T�9�O�O��.}��*9�l�S � VSST~�nW�H�N��e]�i�ꛪA�&@�M��Ez-��j#
0>��B�h��hZ��Q:����"`]���Hh�Ǩ5�$g�DV]�G�K�'~��ۂ�ԓC-4����$�ǢNs�k�4XԤF�7�G�����f
 ����)Н��5i�*5��nc��3A� ՗(�*�
���MQ!T��R�� 8 ��5(�J��s�*dOX�j������U��9|	W�d��)��M� "Z���h5�e3��B� T��My3̲zGZ�0��lVԁ���{������l$����lG)\��qo�lTL�#�>�;LP�kzU���tG����
���̪���S�發��E#�o�0���k�&מ�Rʔ[WNX��t��
��I�ëUNY�MJl�[]�(��L�_�qݏzүs��c��[:�ƚV*�z�pмllE��,�'vm�\И�r{��Ù��}H���]=���k2T�tІchҒ t�h��#��pe��o���<kT���5�f;�k�PX6SU�%\i����n�S5�ӏ�>מ�:j�w��mW�P�`�T��c����`U(7�`�/_�r"�S4Ě`����PV����Adfu��O6�A?�Θ��+�l7K>�(�e��E8YF#�*O4L��p�y��"�������]��!�~�&��z���X�U#�e'��ҺaY�?��F\K��c����	U�v��~Z�9��-�̼�3]��5�T�$:R�od]�d��)�O�䪂V6_���^����8�t����jmuz�)�.2B��LE=�o�0c�8A���)P 񴕫26��Y����Ku������B22�qm
+&�C,�ur���?�T��F�F.���@%�R�r�fY�a",��pΙ�Vנū��{^+��E��Ԫ��艇)Dߦ��g��0l�3�,����0?��q�	@S�z�������n�TW�O�� FVjsnb��]E[p�5Zt�!��r�\?lM�t�!���;��ML{�g��͎�E����Ʒ�䴮�:������0�GkZ�WЀ���97
c��D�q(����=���ߺ����	�Bf��77OK�j������~��d�lL�p8:�RC��X�E�A�� ~R&���ď]ȓ�n;������K�J4������+D�
psg�[y���T?��q�{g���l�'��_6�^.	��q�~�y�ϒ��8��"Rv�57yS1Ѳ��%69���g����i,�lSub0u7]�5m~2e��SGt������5b��O�g�e��O]��z)�Vա�̵�R��Iao�Wa��0c3#�����\��hJ��0b{%����k^�m���G�[�U�\m`�v|�����ضд�+��!`f1,^Z�k���FZ:�[�c5�]�������n��W�S����:�i����=N�M���xG��,-����:t/���荫�_��n�7A7�Y��*�K;F����W?7A����lR��__�*j7��pI3�B��[�_��ldc!4yf�Q��7:s����3�;�`�����6��7#�f�;F�Q�g���1�]�����������;n�5���A��s�7����Y�3�Z����_,Gá����@S��A�Xp+(������S�����3�g�d�7]�d�e��fUw�,v�U���ܠ9��b��]�d��J�ڋ(����Фͺέ`+X�
�̇|*������A4�pկȀ���A�Xa^8��ݡ&O��ej.[���\��9!�j�ᲊ��@t����o���|N�z��HI�'��/
r� #,��8��
 �p��[U?Z�p������#����w�[v�9y��{ˣњH4�!`��!k�f8���N��mn���InV��5� ��W��tu��e�łþ{�`�j�:��o��͆�]��I��#�h�D.�'j�7)o���[��9�YE�6��qlvG��x��eܕ�mH��<Y=�G]ְ5������+{�y���sVWЭv �'ʾ���!e��F�FF�)#�|��D�P=!q�	��W���=�T)����U;�Q���F'tc�WΞ�emO��~�M���ج}!M��3���â��p�����i�.7�k�S;�p��\�W����W�I�{�|��pG�h�K1�ve���pw��$�Dۭ�/�4�,�h���
s]�a���0�DgGk8�vgs۠��Ԏ��}�;�rw�s�KQl����hg�%��J��?,����-�<9���u�<_F��6��Ժt�y�H�_'��_Ӿ͋JD��5�P�xX��[�\G��U��Z��v?�CҷDU���^3.-�K�P�v��ܭ�;N�>����ߡ�������8T԰���`D�>�-NC����"��bD&���dU��[j�t@;�a#Ku�@ؾ6���pж�R�b�ِ��ۯF8oa�L�3"^�h;��R�ݥ%�zG,g O������[�5؀���Zg���m-�DJ:hK��FU�$%�&�7�B�<'*�	\��k&�a��Do�kNX�E���8��Ne�$�݂:goj�����N��ݢ�h#T�􇰜�����n�l�Y@�U@Y\Bo�H��G`���68Ք5�X,��C���шeM�۰�T��r�g4}R3�2�Q_�!;�^tЧ�B��z�v�4��i��~���ǌ4���L6
Wn{��RlF(a�E_%��PӔ��5Rۺ�?y���Y���t�X��W��YJ�E2�E��~Nά,�z���$���z"�t�����}��� ��K|���,�˚2&���mI~�,��Gm��f{��f�˝��ߧM�wq�M?�ȳ��n�mu�7��ͻS�t��3ROY���*��������/9�b̵��ңmw��J}vT߿�':�WW耲���'A (���t�$�m�]��������>�Ev��i�����WC�Z4���U���w1��p�͕u��*d���)4R ���Ts8+%�B��V64w�@ZÀ����E�0s�yawsk�%Ϻ�d���CY�v�XM���>�2��Km:��V�i�[p>�7��!�����-j=˖vt��Dls�AT+oS��$�jK_�l畱��m�i��6mU��.���O5��;��a�+`��{�R/w�M�$+ҬpGzgS�Ϥ�B�' /%��h�ԑ`��*ɦ�_<�����cӉ�-Ǭ����[��Ҭt\+�7=s�2�NoC2y�5.���>Y�x�#�{*+�@1��0�� �^N@����O��#/*�bv����#vH%�0� ��d�]�9{LW��|���~L��9�A9�a�[{]��Sj���s7�_3f�dY��*�Z�������M�sa���&���|�ik�$gal1LfKGz�'Fq�2��{dGư=wԿW��Iܪ�m1�B���#��uy���-�;����D,R��z��vO#�{P/�HY,٢�؟+Uj��ח;.'A���]K�(#���6��e�ExѾO
�D��e��c(��� a+���w����ܓ4%��kWC�&j�7�dۏ[�z=czS����%�p2dgQf�ל��szM5fW<�{�]�e�L;�U�u���nzq��m�O4��l��������K����y����m	�}�;��/U+��r()(arg1_type a1, arg2_type a2, arg3_type a3, arg4_type a4,
			arg5_type a5, arg6_type a6)
		{
			lock_block<mt_policy> lock(this);
			typename _signal_base6<arg1_type, arg2_type, arg3_type,	arg4_type, arg5_type, arg6_type, mt_policy>::connections_list::const_iterator itNext, it = this->m_connected_slots.begin();
			typename _signal_base6<arg1_type, arg2_type, arg3_type,	arg4_type, arg5_type, arg6_type, mt_policy>::connections_list::const_iterator itEnd = this->m_connected_slots.end();

			while(it != itEnd)
			{
				itNext = it;
				++itNext;

				(*it)->emit(a1, a2, a3, a4, a5, a6);

				it = itNext;
			}
		}
	};

	template<class  arg1_type, class  arg2_type, class  arg3_type, class  arg4_type,
	class  arg5_type, class  arg6_type, class  arg7_type, class  mt_policy = SIGSLOT_DEFAULT_MT_POLICY>
	class NUI_API signal7 : public _signal_base7<arg1_type, arg2_type, arg3_type,
		arg4_type, arg5_type, arg6_type, arg7_type, mt_policy>
	{
	public:
		signal7()
		{
			;
		}

		signal7(const signal7<arg1_type, arg2_type, arg3_type, arg4_type,
			arg5_type, arg6_type, arg7_type, mt_policy>& s)
			: _signal_base7<arg1_type, arg2_type, arg3_type, arg4_type,
			arg5_type, arg6_type, arg7_type, mt_policy>(s)
		{
			;
		}

		template<class  desttype>
			void connect(desttype* pclass, void (desttype::*pmemfun)(arg1_type,
			arg2_type, arg3_type, arg4_type, arg5_type, arg6_type, 
			arg7_type))
		{
			lock_block<mt_policy> lock(this);
			_connection7<desttype, arg1_type, arg2_type, arg3_type, arg4_type,
				arg5_type, arg6_type, arg7_type, mt_policy>* conn = 
				new _connection7<desttype, arg1_type, arg2_type, arg3_type,
				arg4_type, arg5_type, arg6_type, arg7_type, mt_policy>(pclass, pmemfun);
			this->m_connected_slots.push_back(conn);
			//pclass->signal_connect(this);
		}

		void emit(arg1_type a1, arg2_type a2, arg3_type a3, arg4_type a4,
			arg5_type a5, arg6_type a6, arg7_type a7)
		{
			lock_block<mt_policy> lock(this);
			typename _signal_base7<arg1_type, arg2_type, arg3_type, arg4_type, arg5_type, arg6_type, arg7_type, mt_policy>::connections_list::const_iterator itNext, it = this->m_connected_slots.begin();
			typename _signal_base7<arg1_type, arg2_type, arg3_type, arg4_type, arg5_type, arg6_type, arg7_type, mt_policy>::connections_list::const_iterator itEnd = this->m_connected_slots.end();

			while(it != itEnd)
			{
				itNext = it;
				++itNext;

				(*it)->emit(a1, a2, a3, a4, a5, a6, a7);

				it = itNext;
			}
		}

		void operator()(arg1_type a1, arg2_type a2, arg3_type a3, arg4_type a4,
			arg5_type a5, arg6_type a6, arg7_type a7)
		{
			lock_block<mt_policy> lock(this);
			typename _signal_base7<arg1_type, arg2_type, arg3_type, arg4_type, arg5_type, arg6_type, arg7_type, mt_policy>::connections_list::const_iterator itNext, it = this->m_connected_slots.begin();
			typename _signal_base7<arg1_type, arg2_type, arg3_type, arg4_type, arg5_type, arg6_type, arg7_type, mt_policy>::connections_list::const_iterator itEnd = this->m_connected_slots.end();

			while(it != itEnd)
			{
				itNext = it;
				++itNext;

				(*it)->emit(a1, a2, a3, a4, a5, a6, a7);

				it = itNext;
			}
		}
	};

	template<class  arg1_type, class  arg2_type, class  arg3_type, class  arg4_type,
	class  arg5_type, class  arg6_type, class  arg7_type, class  arg8_type, class  mt_policy = SIGSLOT_DEFAULT_MT_POLICY>
	class NUI_API signal8 : public _signal_base8<arg1_type, arg2_type, arg3_type,
		arg4_type, arg5_type, arg6_type, arg7_type, arg8_type, mt_policy>
	{
	public:
		signal8()
		{
			;
		}

		signal8(const signal8<arg1_type, arg2_type, arg3_type, arg4_type,
			arg5_type, arg6_type, arg7_type, arg8_type, mt_policy>& s)
			: _signal_base8<arg1_type, arg2_type, arg3_type, arg4_type,
			arg5_type, arg6_type, arg7_type, arg8_type, mt_policy>(s)
		{
			;
		}

		template<class  desttype>
			void connect(desttype* pclass, void (desttype::*pmemfun)(arg1_type,
			arg2_type, arg3_type, arg4_type, arg5_type, arg6_type, 
			arg7_type, arg8_type))
		{
			lock_block<mt_policy> lock(this);
			_connection8<desttype, arg1_type, arg2_type, arg3_type, arg4_type,
				arg5_type, arg6_type, arg7_type, arg8_type, mt_policy>* conn = 
				new _connection8<desttype, arg1_type, arg2_type, arg3_type,
				arg4_type, arg5_type, arg6_type, arg7_type, 
				arg8_type, mt_policy>(pclass, pmemfun);
			this->m_connected_slots.push_back(conn);
			//pclass->signal_connect(this);
		}

		void emit(arg1_type a1, arg2_type a2, arg3_type a3, arg4_type a4,
			arg5_type a5, arg6_type a6, arg7_type a7, arg8_type a8)
		{
			lock_block<mt_policy> lock(this);
			typename _signal_base8<arg1_type, arg2_type, arg3_type,	arg4_type, arg5_type, arg6_type, arg7_type, arg8_type, mt_policy>::connections_list::const_iterator itNext, it = this->m_connected_slots.begin();
			typename _signal_base8<arg1_type, arg2_type, arg3_type,	arg4_type, arg5_type, arg6_type, arg7_type, arg8_type, mt_policy>::connections_list::const_iterator itEnd = this->m_connected_slots.end();

			while(it != itEnd)
			{
				itNext = it;
				++itNext;

				(*it)->emit(a1, a2, a3, a4, a5, a6, a7, a8);

				it = itNext;
			}
		}

		void operator()(arg1_type a1, arg2_type a2, arg3_type a3, arg4_type a4,
			arg5_type a5, arg6_type a6, arg7_type a7, arg8_type a8)
		{
			lock_block<mt_policy> lock(this);
			typename _signal_base8<arg1_type, arg2_type, arg3_type,	arg4_type, arg5_type, arg6_type, arg7_type, arg8_type, mt_policy>::connections_list::const_iterator itNext, it = this->m_connected_slots.begin();
			typename _signal_base8<arg1_type, arg2_type, arg3_type,	arg4_type, arg5_type, arg6_type, arg7_type, arg8_type, mt_policy>::connections_list::const_iterator itEnd = this->m_connected_slots.end();

			while(it != itEnd)
			{
				itNext = it;
				++itNext;

				(*it)->emit(a1, a2, a3, a4, a5, a6, a7, a8);

				it = itNext;
			}
		}
	};

}; // namespace sigslot

#endif // SIGSLOT_H__

