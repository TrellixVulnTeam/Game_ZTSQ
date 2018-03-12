# -*- coding: utf-8 -*-
#tkContentTools
#Assets�t�H���_�̃t�@�C����Resource�t�H���_�ɃR�s�[����X�N���v�g�B

import shutil
import sys
import os

args = sys.argv
assetPath = args[1]
outputPath = args[2] + assetPath
#�R�s�[��̃p�X�ɕϊ�����B
resourcePath = assetPath.replace("Assets", "Resource");
#�f�B���N�g�����̂ݎ擾����B
dict, file = os.path.split(resourcePath);

if os.path.exists(dict) == False :
	os.makedirs(dict)
#�R�s�[�B
shutil.copy2(assetPath, resourcePath);

#�o�̓t�H���_�ɂ��R�s�[�B

dict, file = os.path.split(outputPath);
if os.path.exists(dict) == False:
	os.makedirs(dict)
#�R�s�[�B
shutil.copy2(assetPath, outputPath);
