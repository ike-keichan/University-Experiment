%Keisuke Ikeda%
%744069%

%%������
clear all

%% �ۑ�v���O�����̏����ݒ�
config_display(0, 4, [0 0 0], [0 0 1], '�S�V�b�N', 50, 4, 0) % �X�N���[�����E�C���h�E���[�h�ɏ����ݒ�A���̑��̓f�t�H���g�ݒ�
config_results('myExperiment_res.txt'); % �o�̓f�[�^�t�@�C���� myExperiment_res.txt �ɐݒ�
config_keyboard; % �L�[�{�[�h�̏����ݒ�
 
%%�ϐ��̒�`
%actionNumber = ['�@', '�A', '�B', '�C', '�D', '�E', '�F', '�G', '�H']; % �e�ʒu�̊��蓖�Đ������`����B
xPosition = [-320, 0, 320, -320, 0, 320, -320,0, 320  ]; % ��������������x���W���`����B
yPosition = [256, 256, 256, 0, 0, 0, -256, -256, -256]; % ��������������y���W���`����B

%% cogent toolbox�̋N��
start_cogent; % cogent�֐��N���i�X�N���[���A�^�C�}�[�A�L�[�{�[�h�o�b�t�@�Ȃǁj

%% �Ŏ��_�̏���
preparestring( '�E' , 2 ); % �X�N���[���o�b�t�@ 2 �ɌŎ��_�i�E�j��������
 
%% �ۑ莎�s�̃��C�����[�v
for i = 1:30 % �ۑ莎�s�̃��C�����[�v�����s�񐔕��J��Ԃ�
    
    preparestring( i + 1 + '���' ,2, 0, -256); % �X�N���[���o�b�t�@ 2 �ɌŎ��_�i�E�j��������
   
   %% �h�������̏���
  random = randi([1, 9]); % �h�������������_���ɂȂ�悤�ɕϐ����`����B
      
   %% ��ʂɎh����������������
   clearpict( 1 ); % �X�N���[���o�b�t�@ 1 �̓��e���������Ă���
   for j = 1:9
       if j == random
           preparestring( '�X', 1,  xPosition(j), yPosition(j)); % �X�N���[���o�b�t�@ 1 �� �Ǎ��񂾎h��������������
       else
           preparestring( '�k', 1,  xPosition(j), yPosition(j)); % �X�N���[���o�b�t�@ 1 �� �Ǎ��񂾕�����������
       end
   end
   
   %% �Ŏ��_�̕\���Ƒҋ@
   drawpict( 2 ); % �Ŏ��_��������Ă���X�N���[���o�b�t�@ 2 ����ʂɕ\��
   wait( 500 ); % �Ŏ��_���\�����ꂽ��Ԃ� 500 ms �ҋ@
   
   %% �h�������̕\��
   drawpict( 1 ); % �h��������������Ă���X�N���[���o�b�t�@ 1 ����ʂɕ\��
   
   %% �h�������̑ҋ@
   t0 = time; % �J�n����
   
   %% �L�[�{�[�h�o�b�t�@�̏���
   clearkeys; % �h���掦�܂ł̃L�[�{�[�h�o�b�t�@���������Ă���
   
   %% �h�������̑ҋ@
   waituntil( t0 + 2000 ); % �h���掦���� t0 ���� 1000 ms �o�߂���܂őҋ@
   
   %% ��ʂ���h������������
   drawpict( 3 ); % ����������Ă��Ȃ��X�N���[���o�b�t�@ 3 ����ʂɕ\��
   waituntil( t0 + 1500 ); % �h���掦���� t0 ���� 1500 ms �o�߂���܂őҋ@
   
   %% �����f�[�^�擾
   readkeys; % clearkeys�ȍ~�̃L�[�{�[�h�o�b�t�@��Ǎ���
      
   %% �L�[�{�[�h�o�b�t�@�̎擾
   [ key, t, n ] = getkeydown; % readkeys �œǂݍ��񂾃L�[�{�[�h�o�b�t�@�̓��e����ϐ��ɑ��
                               % �����ꂽ�L�[��ID�Fkey �L�[�����������ԁFt�A�@�L�[���������񐔁Fn
   
   %% �����f�[�^�̏ꍇ����
   if n == 0 % �P����L�[�������Ă��Ȃ�
      responce(i) = nan; % ������responce��nan�ɂ���B
      RT(i) = nan; % ��������RT(i)����nan�ɂ���B
   else % �P��ȏ�L�[��������
      responce(i) = key(1); % ������responce��1��ɂ���B
      RT(i) = t(1) - t0; % ��������RT(i)���v�Z���đ������B
   end
   
   randomMemory(i) = random;
   
   %%  myExperiment_res.txt �Ɍ��ʂ��o��
   addresults(i, randomMemory(i), responce(i), RT(i)); % �L�����������f�[�^�̃t�@�C���o��
 
end % ���s�̃��C�����[�v�̍Ō�

%'myExperiment_res.mat'�Ɍ��ʂ��o��
save('myExperiment_res.mat', 'randomMemory', 'responce', 'RT', 't0');
 
%% cogent toolbox�̏I��
stop_cogent; % cogent�֐��I��

