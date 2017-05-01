//  **************************************
//  File:        FilePath.cpp
//  Copyright:   Copyright(C) 2013-2017 Wuhan KOTEI Informatics Co., Ltd. All rights reserved.
//  Website:     http://www.nuiengine.com
//  Description: This code is part of NUI Engine (NUI Graphics Lib)
//  Comments:
//  Rev:         3
//  Created:     2017/4/12
//  Last edit:   2017/4/28
//  Author:      Chen Zhi
//  E-mail:      cz_666@qq.com
//  License: APACHE V2.0 (see license file) 
//  ***************************************

#include "FilePath.h"
#ifdef ANDROID_NDK
#include <sys/stat.h>
#include <linux/ncp.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include "CharSet.h"
#define MAX_PATH	(260)
#elif defined(IOS_DEV)
#include <sys/stat.h>
#endif
#ifdef LINUX
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#endif
#include "CharSet.h"

#define UP_DIR_STRING	_T("..")
#define CUR_DIR_STRING	_T(".")
#define SPLIT_STRING	("#")
#define SPLIT_CHAR		('#')

kn_char s_DataPath[MAX_PATH] = {0};
kn_char s_CurrentPath[MAX_PATH] = {0};
kn_char s_SavPath[MAX_PATH] = {0};
kn_char s_SavUserPath[MAX_PATH] = {0};
//	系统使用的数据文件名,全路径,用于判断数据是否受控
kn_char s_wszDataFile[MAX_PATH] = {0};

// 各模块相关路径
static KModulePathMap s_mapModulePath;

/*
* 函数功能：设置Data目录
* 参数：
*		path [in]：Data所在目录
* 返回值：无
*/
void SetDataPath(IN const kn_char *path)
{
//#ifndef IOS_DEV
	_tcsncpy(s_DataPath, path, MAX_PATH);
//#else
//	#ifdef UNICODE
//		swprintf(s_DataPath, L"%s/Data/\0", path);
//	#else
//		sprintf(s_DataPath, "%s/Data/\0", path);
//	#endif
//#endif
}

/*
* 函数功能：得到Data目录
* 参数：无
* 返回值：Data目录
*/
const kn_char* GetDataPath(void)
{
    return s_DataPath;		
}

/*
* 函数功能：设置Data文件名
* 参数：
*		path [in]：Data文件名
* 返回值：无
*/
void SetDataFile(IN const kn_char *path)
{
    // 	memset(s_wszDataFile, 0, sizeof(s_wszDataFile));
    // 	_tcsncpy(s_wszDataFile, path, MAX_PATH);
    memcpy (s_wszDataFile, path, sizeof(s_wszDataFile));

}

/*
* 函数功能：得到Data文件名
* 参数：无
* 返回值：Data文件名
*/
const kn_char* GetDataFile(void)
{
    return s_wszDataFile;		
}


/*
* 函数功能：设置Sav目录
* 参数：
*		path [in]：Sav所在目录
* 返回值：无
*/
void SetSavPath(IN const kn_char *path)
{
    _tcsncpy(s_SavPath, path, MAX_PATH);
}

/*
* 函数功能：得到Sav目录
* 参数：无
* 返回值：Sav目录
*/
const kn_char* GetSavPath(void)
{
    return s_SavPath;		
}

/*
* 函数功能：设置用户的Sav目录
* 参数：
*		path [in]：Sav所在目录
* 返回值：无
*/
void SetSavUserPath(IN const kn_char *path)
{
	_tcsncpy(s_SavUserPath, path, MAX_PATH);
}

/*
* 函数功能：得到用户的Sav目录
* 参数：无
* 返回值：Sav目录
*/
const kn_char* GetSavUserPath(void)
{
	return s_SavUserPath;		
}

/*
* 函数功能：得到完整路径(Data路径 + 文件路径)
* 参数：
*		strPath [in|out]: 路径信息
* 返回值：无
*/
void GetFilePath(INOUT kn_string& strPath)
{
    // 	kn_char cBuf[MAX_PATH] = _T("");
    // 	_stprintf(cBuf, _T("%s%s\0"), s_DataPath, strPath.c_str());

    kn_string strTemp = strPath;

    strPath = s_DataPath;
    strPath += strTemp;

    //strPath = s_DataPath + strPath;
}


/*
* 函数功能：得到路径
* 参数：
*		allpath [in]: 完整路径(路径 + 文件名)
*		path [out]: 路径信息
* 返回值：无
*/

void GetPath(const kn_char* allpath, kn_char* path)
{
    kn_int len = _tcslen(allpath);
    kn_int i;
	kn_char szMatch = 0;
#ifdef LINUX
    szMatch = _T('/');
#else
	szMatch = _T('\\');
#endif

    for ( i = len-2; i >= 0; --i)
    {		
		if (allpath[i] == szMatch)
        {			
            _tcsncpy(path, allpath, i+1);
            path[i+1] = 0;
            break;
      ����sУϸ�5�ܪLN[�/2�q�=������r#K�Q���]��<e�M�<���09Be7
�&�qRp`�т���k.�vZ�6I�����9���h���T�o��G���F*s턮�*j2���j�����S���9;�y_+��X�M��tkk.8

9��@�
U��L�L)�fm3Y�p:��L.Τs@���T�~z��'�s��a80� ��K��]-	LTk=w�k��|��H&߼`oZO $us}o�,��)����&;�ѻFw_�W��^1Jp�Qq�C�S�ҩͰiP�:G9J͔�:�y�1Y�<l��@�B���8�F?eVO�+N-�9ң�n��P��8������Y�<[~~3��R}i��4T�f8���-A���c���d��N�x��;?4�	kH�U��� �I��7-��02��:�QRK��x��j7R�������<Fe��gKɦ�"���H��xFA��iN�E�*�޴�gy��iHtf�1�ᔤ$Z�uAg(��AN��?�Pq�<*��(�7�"�|B�����f�(��yԉ`\��b���U���0�S�NEi,C9�����P��B�@^E�a!txp�P�#^@��E��,{��a4��Y'(��?5��[gd��"�{��Aщ�����*:(�@�O����ˁ��^i�i)(�j�Ny`6��(Z�A=���K���\#�+�x[��E����	Ha�S��IN��Ηz(.v���7}�aZ��;k5��jT��{8>���|P�iI�$�6�6TKro"�B�T�I�nEU��py^ߵ����.�1��2oNzH��A�˱�Nz�wv��9*1���z�N:�Щ��$�򩷷W�Ǒ��j�a��}���q$D��J�x���zV�[3VT�����+%������0��+E��b�fܮ��n���jГ"�jH�Kc�NOc�	��Q���g�ۤ���w�#�,c~9��/�.$g��ltzb��$с�ͽ8؀��h�ĮT���X3=��_$��W��i�cfϭ7�{3|��yQ�r��`%�Z;��p�R�b�I���H�u�Aq=mկ͐$��xK�_t��'�ϮN�!l[�V�[�TZo�[�>�Q3����Q��<���I��o<�`9x�e�����'�F*f� 	'��}��N����^���W#~�M�(��� �4��p�RL���Gb:���!�2\nx���>D��_���GSO��C�'8�U8�d��*�d~*����=X��K�%z���L�P��櫒	F�)!���F�I\�*=[��qDq�@�:ܸ��K�j|��{e`������S"�b���E��׋����Ҁ񜳰�-������1�9�
�)��6nY���PG
����4�����g����~M� �c1�����Wڢ!����I�b�9��XF��,�'h�>�;�=0�I ��W��zf�`h�{�0�x�]y`��c��
b�d�l,�K8f@/0�;��i?�6٢;�F��l�-�춳�`x�YpA�"�>ωy{zV�}X�y����J� �;�fCl)��0���F��R��q�4���2���O �b���bGAl:���o%�r;��B��@4��0�	'� 3���  a_dk�س)4¾1[��Y,�}�Al3��f��q$�LZ��>����ci�)^Q���E��-P�V�Pxdj�����z�{��e��\�2����� C)������V���yhq-?�a�h����6�!�z�8{>��b%��S>�)-P߻�l��,^�N�~L��W��ƾ�	J�#���"�X��q������VK�=��"���� X�d��dY2���L�TE}�E1�X �?f��B��fq�:<�J���d�!L�o'�}SAK<-q`�(G�����c@O��Y4���;b�e�cXq�*X��[�'�7����N��sq?��,� ��>pK7�}tr����X�"��-��4�%?���+�Ţ^a}�#�O�,���h<y%	$>�T�VF8�x��rC��G�p/���;h,�}y���u��Z����^����u�׽QXԋ�~�6ìъfXqGh3�o�����`(K�M1�eS<Y߹)ok
�P��&C�2�e�G�t:�A=�F?�`�����A㻤�V�����)�BE%�A�:�a��şB�#,
���N�^ ��&��!1�%6�zo���XT��G����7A!����"�ằ?����}2}��n�#,�D�dl�M��ۂ+��f�����XR,k��7�9��c�j�LY8�d�����=���rB�����S'`��T]��4}��m��_��˲�ߏ��Dף�'�$es�D傔O�9Q�me�T1�/a�y����P'��%��uRN�G�X�cR�x��h�� 쯁�Q[�b!�b�Cl�����M�ؗY,���ؙ[�b!�[�$�nHX� �)%�!aK���"%�BBK���j)�EHH`	���� �K�����&	; �ǉ4��E[��,�>���>c	�m�4�'	���Z=H�?%W���(��m�|2st�1�`M�Tj�
��ߴE��u�C:�������N�)�W(�V���4:���J:� �b�:��Xハ��J~�F~'�[ɿ<�Ĺ��;��4�Ǔ�U��������G�N�1�Z�O��5�?.:�Aۯ����Y��8`�~�`�v���^��g��6���XH͝��o܆�=��a8hY�B8��9��!{�T_@=ж��BEl[�9����E�v��tڙJ�} a��n�]	��@�V���77��� Y��QO����ף"�M�r�#N���X�ǳߪ��|J������m=��6��@���i�?��������ŕ�"�%p�0zc�^Y�7 SЫ^
��Rk������-T�R~R�ʰS2�KT�Q�B��ͺ�aX�ܯA��[4�w�Áx�2J�	Խl���g0ƚ�k��Gmք�ܶ$��~�ڀ���5rQ�-Qk��s��Vp�b���޲:0��DuVW�eV�X-��{q������*���*� ���
zs�����Fe��7����L��E=SyW��w�U������)�<�*YjTV�Q9ꓩ|�J�r�"�qÇ	#����60$8MW@swB6#�T�(G�m ��j�Y���/��'KTjbY�JM�_�5qp�\#�ըը<�e*T>~���������wY��NU�54�
��
��\S���v����(��u��~8-WW�����_^��k~>	�10�J+�EwF��#
U���ûs��^q)�P�!�p�I��ܫ��n�{��y��%���S�7����dp��������^�/p���~i=��A5|��� U�Ξ싲{@��}�{�I5ܓOFZI��^s R|~����o"���~5|����T�?�D����S��;H�9N��w�/�N�*�����ۏ���t<�z��^5|ho���P�_��iU���E�oe���"�wO������}}L_��H�y?W�����]���#��*U�F����j��:)�5{��-�)�����}�u����V÷{w���T�ˌ��U�L�Qu�k싹��]j������U�>�i=�j�����}j��G��U����+5|�}�m��FuΨ�܃T�>{$�z��Z_Cu��Q�W1���Y"���z5|�G�oK���UE��fU����ɜ����}����y_FZ�;�������}v�/���5�����P���H�A�ʫ�2R|+�P���}Q�Y�j�'W�w(�E|��F���TD��ZU�}r���U����/p/T��)���'W�W�7��_���>����Q����/p_�ʷ��>�ٜH�C^��^�6���y���$��n���Fl�U��>�%3 ޹�����k5Z��h��Q���_�����.��F>&O�F~�c�DM��>�F��^P��*qjT�퓩8T��]P�V���8x���Iou����Y)j23^�!
f?b��)����U+O����&a%}�K�{ћQ�I�ڔ帍��v�E�{�r��%����ɾ:{.�r��7%�i��+���J��J�D�ur���h�J���M �,|�/'�����sw�4(��m񠱎_�T�E�ǘ+v�qh]'��OC�	��[%����i�C�	��S� z��N@��%��˒�-���u!��b���n���O���[�;�1�o�5jf��q�R�����|LR�vF7|�ix�'8�!�4<d!qh`Xf�UG��@���������j�wb�ʜ��c�z% ��/�ߟ���`�xβ�;q��Ξ�P��9�~�̙�+�B����*��R#�A����R�e��rY�F�C�
���dZ�(h͵���=8Me!��F��G�B��\�?�M�Ţ�F��Q��Y+S�PP�sWTz5�fNs=�c�c�<�j�d���f���	����T�H���HV�.�G>��e�.����1�q��fם*�2�3�f9�a`�4����-[eܨ󀯽�S���on���`����M)�&����w?w�^�sTF�I���[��e�y$���\�u��˲U�tmW��2�'�ƥr�g�4��j$�~ �'�R�M�y�X�F��OU�\�S�2BA�>U*t��18�H���*0{�gk41PU�!��=�����k��X�Lo'�w�M0���N0���̱�r͙�웉�)a|���*�+e>
|�kJ��1'��:����2�����h�X���
��L���z۪2��Xe����e�L��i��X5*K�2��
*�3��N�\�T���!.�����΋����Y��l6���7��8�B�Ft<mi<ԮTd�Mrg$Sgb�'oҕ�oJ'��V���7)ɱ�վK�#����&��,������aM�m�f��xMT�@Cw���HH�j�T�7�#��m�֮<0���O��&�A��%%$�D���Z�S�`B�Q�3h,�׾F[[%i�licKc	���4���	�;���w߼w��(�6�w~�{߽��{�j���i�^+��6l�H��촃c��������H�5g� ^��X�7�z��p�5K��c�>�X�2+a��0²�Iʲ��� %K!��GiHQO���+2�HnڄD��F�'�v᫝� �'�+A1��F?�U	q``'l�Ֆ�5?����P�����3���ݐ<����g��<O�O�<7�w)��	B��;�0��8eVҏ2���z�� �ƀNﶴ�إ����w'aXg X��)V#	�g(��$Օ60�}h��7�Կ$�<�K�tRi�I��y1]I�	l��O��b�S�	�y�1���x:��mnb���c�/T0�1�19t�29؇2�:�.b~�@$��~����wCnuDPLJa
Eyԛ��UCq�kW�Iֵ��=ڵۼ�v�&K�S:��.f��G�w(�G(��^���]�J{�Rik|�������N�E+����6�1���"X�P�r�>*Xh���f���S��X�0;��f��ֲ�����m�Khc�k�ī�p^xa��J~�t�N�CR�M蔍7w��{��8!�v�H2�'�^��I�x��I\��*�_v@����$��a�$��A���Hb��sݍpb������k+*y�Z��!��Oy@#�ܱ'݊��݊���z/L�%	�9C{u��M}�g2-D6	p.�fy�L��ec$p�-pd��O������/��E�3��b��>��`J�>���丗��_jh�D��ͶE�juƳ����7��\��N������vtE�Mз�/s=�m��b���U�L{H١��h���꿺�`��=���n�����[�r����e����fρ�5n���'�(�v���7ԣ$��j��α}��T��s���v2��w�T��)�߂)U_;T�����Q|�r~ȷ����7�o�&�~���︄�)Xk����X.���\ҍ����:K޻>MP>{o*�D�F�lށ���@���|z�s>�(�����?�Ͼ�|�H�k��q��7���̯ގ��&�i��3����m�M�󥯌��1y����7�m��F���!Yv�K�R�P_���!���*������mm�=�re+�2f-E��:�r�A���\�KQ�w�(�j(�ag��I�\����i�Wf
�V�~\kb:7[#���xemAx�[c�<y���W�Vy'�*GA�7B�3Fj�Jj}gJ���9@עmK�
&?bLo���WS&�I���'L
n*��Ƙ4ǘ$�Lu�L����Cm�R���BH�ڄ�j�5%�gGI����Ro(Hu�H9a�>��wFHH�ie/��Al�k�VIڿ I��ʁ�J+���PVIB7+%(w[b(�-��y��)<ƕ�{����NٓVeژW&�R�����}j�F������
��~��+��N�<�&�
O�Y�wH�?	��v
ˈ��g��A�_A?cf
Q����R�A���L�NQ&HP5�܌����h��r�y�^�k�n:B�7������%��m�7������uH�7N����������=�A��PL[)�b	���
9C "ٱ�{��g��?�t�-�j�͍�e�[����L7ɴ$_���ʃ�cf/�4�D땨����f`}��uW�uv������S�R�-�n&?����X�{�}�fhƄz��4�8�m��hּ�#s���l~-��>�4�$�M�[D�%�e+����O84�K�7ƽq\��E�-vCq��Z��bl��dV���'�y�|������B����ؼ<����+��l;��^S̊6r�r��<ND.��Q�T=���Z�D��ᆄ+��L��Ba�1���Cgr�<1���\��H��1�iٛZ�!�"i��ٟ�J��Α0�CB��c�a�e�u��B�T��S�PeNM��t�/��Я/�ϜcǸ�N[�����-�_g�~��>A�~����F�b���IH383RT��O�^b2�9�4ƒr��9n2�\.�ʿ�uEa6�V2@W�w=i~��C��x��	�!��C[ҭ¦eV�GB �V"bcq��OZ�ȑF�N5ð��@�4(�C�z�`ў��-��S��=���gۗ���u��b=8�d�~Q�鎑IX��������Mɴjh�;�A4� %���<	DF�]������:�Om	���������ú����}^�D���(VS+�++p-��*�2�XhխúF ]ٜ6�0Oɉ{���������_�Z�Lr��d���#//� {9I�r���_d��.�|sH�i{�a.���i᪩�zgCMs���%���/x�<��fm{�-���m�N^������z������`�B��ϖ�D/��n�(=�<��<Ҿ�<R[PU��`"�	W�+}�T���9t��9ß�]=a%�0�!����گ�ៜ����z�I�|Ii���
&�^��w}ŖbP�E=���.��_W�)pF3<AQ�T�� W��Ơ8�(�t�&D�8_ ��@PLA���"Q�&� D1�#P4B}G��
��GO�#�F��:�88��b�dP�@'�(NO�Q����P����(楂�)��w :D1�/�)����E_�V�C���"Q�"�X�(X�j6�x]���E
8��0D��Px!��@QQ\��WNJń\P�#�J��@G�Aq Q��Q�#5*Q_���(�f����%�Ť��pG�	��bdP<�(7H�\F�@��(⧃�D1�Et��0J����������v��Z8~m%�u�<��M���?�M�Ý���A�A���u@:���LI �r�HH�l��}�6 �AƁ�Y���}�2�kz]+�P�� �@�@�������u��	HW�! �A�l9	r�	H�z]C�� ��,�$$$�o��@���*�S��ݛU|T�tդ@�G5�]�Gik���:�T|�^�i��\۩���]T|�{�����T|��a*>��`�<R�G��W�G5��W�Q�Ʃ��:�T|��1*>j@�����\�GEU�QݓU|TTM�$Z�G����܋U|ԩ"u5Y�G�Q�QsΪ���WU|��l�tM�GU���*�Q�Q;z�����T|TN}u鲊��鬊��xN�G=�Y�G�����T|Ԫ�*>j������T�G��������Q7�`>j{w�GM��Qn�0���G}����Y��?�\�� �[z]S�@�� ��T�� OA������D�L�d�Q�+ � ιz]]�� }A&��Yr�g� �Aj���A����Y������K�����(�*�!�y��2>��B��7��H������,�$��������!Aܞ��닂�Ø��s���1I3ə��a�k#S�F\ץ��w+�d{fm6_��u�c����<�$�J2�F0M���N�����Fn)r����FMy��.yů�����1h��<�ECn:ԩ9�i
]���_���	�Tr�Q$��U�'؂da�Ad�=��#�U���e(�={�e����ѝ܀�^۶�\ۗ�fhτ�/4��d�0�U��b��)wv%��tq6�%k�ϚK�9�"�� 3D��V u	����n�׈��֭��Œ9�����;K�9�r6��r�lF����F�l��h�	qI~Ƅ�`Lτ�/e�9+~S�)��e_`d9~�~\
�[�,,�Y�5�?�$,~M�%�{�%N���&�=I�{�W�֪Ə��HDNx�#A@O�!�n!d�S4LZ�ռ`{��d�ǿx���4^`3gj�$9��]�L��3�9�m�9gR69�3�\�9�:ə��sf��4g���䌹�G��8��fq����m(�'��4
����C�����<d�R��m�����V��W*5u_n��p?��wY#��CcL+3������T��
o��K�Fa������An�ܪ9(�y�ˉ�����2f8�g�E{�%_��a���,F�Z��̺b ���OS��yn�?�M
CC��e��Xo@L��cL&˘��f@��`Lz���]f&�h��I�)��ʇ�x({����P���!� ��6[32��۸њ_��T�\e*�r�s��YK�����!����g)��V�:ãؓ�9h��z�����܅��eG��i�|���j�y�2�����m@v��0�x󮶫0!��v�y����̍A�ͨτfs���lW�~c%�f�^�_�;�����to]o+݉kIwfEy��D��-�:ݝ]i���*�F�W�Bo����c�5�ی*Sx�w�fަ�e�lK��4fo^��ټPD��J���^�(y�O�^�X��M��\�)�n-�$�n�����Y1�3n���p��Cm�X���?�7S�4fKQ��^��9a�9�U1tu�������#��F����L�����_+�n�KU3�J3�����#��]|���3�iM��>�ﭑ�!�-5J����@Hp8�_7p�9���l[����%�U�ᤳW���5ª�j���љ�3�������:)��oDg�0J��J�t�����x���#���$�ٞ�hSҥ�}��C��P��R�%��N�Q�`(���)J	�����X��l��^��TCQ���Ϊu&��`��ƬU�~;v��v4ߨ�2:K�P�Nj��[#kHzaz��MK[ѯ?��]�T8bv�=�������e�q��|/k�'g�
ׇ)�G�只-ߚ~G}}��x���M)�����9���D�jD�hLo�]4�S4�PbԲjOu��]��u4�n������	wd'��#��e�yءJ������e�В~�AI}	&!�.'4n��8'5s�5���L�2R�G�J+�x'���LA*{�����Z�V����6)N�{J����xY>���K�D��: