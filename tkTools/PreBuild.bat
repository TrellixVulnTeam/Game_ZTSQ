rem Visual studio�̃r���h�̃v���r���h�X�e�b�v�̃o�b�`�t�@�C���B
pushd ..\\Game\\

rem Resource�t�H���_�̍쐬�B
mkDir Resource > NUL 2>&1
if errorlevel 1 goto NEXT0
:NEXT0

pushd Resource

rem modelData�t�H���_���쐬����B
mkDir .\\modelData > NUL 2>&1
if errorlevel 1 goto NEXT1
:NEXT1

rem sprite�t�H���_���쐬����B
mkDir .\\sprite > NUL 2>&1
if errorlevel 1 goto NEXT2
:NEXT2
popd
popd
exit 0
