%% �ۑ�v���O�����̃^�C�g���Ɛ���
% SAMPLE1  - �P��h������̓t�@�C������Ǎ���ŉ�ʒ掦����ۑ�v���O����

%% �ۑ�v���O�����̏����ݒ�
config_display % �X�N���[���̏����ݒ�
               % �f�t�H���g�̈����� 
               % config_display(1, 1, [0 0 0], [1 1 1], 'Helvetica', 50, 4, 0)

config_data( 'sample1.dat' ); % ���̓f�[�^�t�@�C���� sample1.dat �Ɏw�肵�ď����ݒ�

%% cogent toolbox�̋N��
start_cogent; % cogent�֐��N���i�X�N���[���A�^�C�}�[�A�L�[�{�[�h�o�b�t�@�Ȃǁj

%% �ۑ莎�s�̃��C�����[�v
for i = 1:countdatarows % �ۑ莎�s�̃��C�����[�v����̓f�[�^�t�@�C���̍s�����J��Ԃ�
   
   % ���̓t�@�C���� i �s 1 ��ڂ̃f�[�^��ϐ� word �ɓǍ���   
   word = getdata( i, 1 );
   
   % �X�N���[���o�b�t�@ 1 �̓��e���������Ă���
   clearpict( 1 ); 
   
   % �X�N���[���o�b�t�@ 1 �ɕϐ� word �ɓǍ��񂾒P��h����������                
   preparestring( word, 1 ); 
   
   % �h���P�ꂪ������Ă���X�N���[���o�b�t�@ 1 ����ʂɕ\��
   drawpict( 1 );
   
   % �h�����\�����ꂽ��Ԃ� 1000 ms �ҋ@
   wait( 1000 );
   
   % ����������Ă��Ȃ��X�N���[���o�b�t�@ 2 ����ʂɕ\��
   % �i�܂�A�h����ʂ������j
   drawpict( 2 );  
   
   % �h������������Ԃ� 1000 ms �ҋ@
   wait( 1000 );
   
end % ���s�̃��C�����[�v�̍Ō�

%% cogent toolbox�̏I��
stop_cogent; % cogent�֐��I��