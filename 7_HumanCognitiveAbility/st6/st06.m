%Keisuke Ikeda%
%744069%

%% �ۑ�v���O�����̏����ݒ�
config_display(0, 4, [0 0 0], [1 1 0], '�S�V�b�N', 50, 4, 0) % �X�N���[�����E�C���h�E���[�h�ɏ����ݒ�A���̑��̓f�t�H���g�ݒ�
config_data( 'st06_dat.txt' ); % ���̓f�[�^�t�@�C���� st06.dat �ɐݒ�
config_results('st06_res.txt'); % �o�̓f�[�^�t�@�C���� st06.res �ɐݒ�
config_keyboard; % �L�[�{�[�h�̏����ݒ�
 
%% cogent toolbox�̋N��
start_cogent; % cogent�֐��N���i�X�N���[���A�^�C�}�[�A�L�[�{�[�h�o�b�t�@�Ȃǁj

%�S�V�b�N��, 25px
settextstyle( '�S�V�b�N', 25);

%% �Ŏ��_�̏���
preparestring( '�E', 2 ); % �X�N���[���o�b�t�@ 2 �ɌŎ��_�i�E�j��������

%�t�H���g�F�F�F
setforecolour( 0, 0, 1); 

%�S�V�b�N��, 120px
%settextstyle( '�S�V�b�N', 120);
 
%% �ۑ莎�s�̃��C�����[�v
for i = 1:countdatarows % �ۑ莎�s�̃��C�����[�v����̓f�[�^�t�@�C���̍s�����J��Ԃ�
   
   %% �h���P��̏���
   word = getdata( i, 1 ); % ���̓t�@�C���� i �s 1 ��ڂ̃f�[�^��ϐ� word �ɓǍ���
      
   %% ��ʂɎh���P�����������
   clearpict( 1 ); % �X�N���[���o�b�t�@ 1 �̓��e���������Ă���
   preparestring( word, 1 ); % �X�N���[���o�b�t�@ 1 �� word �ɓǍ��񂾒P��h����������
   
   %% �Ŏ��_�̕\���Ƒҋ@
   drawpict( 2 ); % �Ŏ��_��������Ă���X�N���[���o�b�t�@ 2 ����ʂɕ\��
   wait( 300 ); % �Ŏ��_���\�����ꂽ��Ԃ� 300 ms �ҋ@
   
   %% �h���P��̕\��
   drawpict( 1 ); % �h���P�ꂪ������Ă���X�N���[���o�b�t�@ 1 ����ʂɕ\��
   
   %% �h���P��̑ҋ@
   t0 = time; % �J�n����
   
   %% �L�[�{�[�h�o�b�t�@�̏���
   clearkeys; % �h���掦�܂ł̃L�[�{�[�h�o�b�t�@���������Ă���
   
   %% �h���P��̑ҋ@
   waituntil( t0 + 550 ); % �h���掦���� t0 ���� 550 ms �o�߂���܂őҋ@
   
   %% ��ʂ���h���P�������
   drawpict( 3 ); % ����������Ă��Ȃ��X�N���[���o�b�t�@ 3 ����ʂɕ\��
   waituntil( t0 + 1000 ); % �h���掦���� t0 ���� 1000 ms �o�߂���܂őҋ@
   
   %% �����f�[�^�擾
   readkeys; % clearkeys�ȍ~�̃L�[�{�[�h�o�b�t�@��Ǎ���
      
   %% �L�[�{�[�h�o�b�t�@�̎擾
   [ key, t, n ] = getkeydown; % readkeys �œǂݍ��񂾃L�[�{�[�h�o�b�t�@�̓��e����ϐ��ɑ��
                               % �����ꂽ�L�[��ID�Fkey �L�[�����������ԁFt�A�@�L�[���������񐔁Fn
   
   %% �����f�[�^�̏ꍇ����
   if n == 0 % �P����L�[�������Ă��Ȃ�
      responce(i) = 0; % ������responce��0��ɂ���B
      rt(i) = 0; % ��������rt(i)����0�b�ɂ���B
   elseif n == 1 % �P��L�[��������
      responce(i) = key(1); % ������responce��1��ɂ���B
      rt(i) = t(1) - t0; % ��������rt(i)���v�Z���đ������B
   else %�P��ȏ�L�[��������
      responce(i) = 0; % ������responce��0��ɂ���B
      rt(i) = 0; % ��������rt(i)����0�b�ɂ���B
   end
   
   %%  �����O�U.res �Ɍ��ʂ��o��
   addresults(i, word, responce(i), rt(i) ); % �L�����������f�[�^�̃t�@�C���o��
 
end % ���s�̃��C�����[�v�̍Ō�

%'st06_mat.mat'�Ɍ��ʂ��o��
save('st06_res.mat', 't0', 'responce', 'rt');
 
%% cogent toolbox�̏I��
stop_cogent; % cogent�֐��I��

