%% 課題プログラムのタイトルと説明
% SAMPLE1  - 単語刺激を入力ファイルから読込んで画面呈示する課題プログラム

%% 課題プログラムの初期設定
config_display % スクリーンの初期設定
               % デフォルトの引数は 
               % config_display(1, 1, [0 0 0], [1 1 1], 'Helvetica', 50, 4, 0)

config_data( 'sample1.dat' ); % 入力データファイルを sample1.dat に指定して初期設定

%% cogent toolboxの起動
start_cogent; % cogent関数起動（スクリーン、タイマー、キーボードバッファなど）

%% 課題試行のメインループ
for i = 1:countdatarows % 課題試行のメインループを入力データファイルの行数分繰り返し
   
   % 入力ファイルの i 行 1 列目のデータを変数 word に読込み   
   word = getdata( i, 1 );
   
   % スクリーンバッファ 1 の内容を消去しておく
   clearpict( 1 ); 
   
   % スクリーンバッファ 1 に変数 word に読込んだ単語刺激を書込み                
   preparestring( word, 1 ); 
   
   % 刺激単語が書かれているスクリーンバッファ 1 を画面に表示
   drawpict( 1 );
   
   % 刺激が表示された状態で 1000 ms 待機
   wait( 1000 );
   
   % 何も書かれていないスクリーンバッファ 2 を画面に表示
   % （つまり、刺激画面を消去）
   drawpict( 2 );  
   
   % 刺激が消えた状態で 1000 ms 待機
   wait( 1000 );
   
end % 試行のメインループの最後

%% cogent toolboxの終了
stop_cogent; % cogent関数終了