%% 課題プログラムのタイトルと説明
% SAMPLE6 - 単語刺激を入力ファイルから読込んで画面呈示、これに対するキーボード入力を
%           読み取って記録する課題プログラム

%% 課題プログラムの初期設定
config_display(0); % スクリーンをウインドウモードに初期設定、その他はデフォルト設定
config_keyboard; % キーボードの初期設定
config_data( 'sample6.dat' ); % 入力データファイルを sample6.dat に設定
config_results( 'kekka1.txt'); %出力ファイルをkekka1.txtに設定

%% cogent toolboxの起動
start_cogent; % cogent関数起動（スクリーン、タイマー、キーボードバッファなど）

%% 固視点の準備
preparestring( '+', 2 ); % スクリーンバッファ 2 に固視点（＋）を書込み

% 'A'キーが押されたら課題（forループ）が始まる
% Tstart = waitkeyup(30000, 1)

% 'Esc'キーが押されたら課題（forループ）が始まる
Tstart = waitkeyup(30000, 52)

%% 演習６ 課題開始の制御 %%%%%%%%%%%%%%%%%%%%%
% waitkeyupコマンドを使って、
% １．'A'キーが押されたら課題（forループ）が始まる様に
% 　　してみよう
% ２．'Esc'キーで始まるためにはどうすればよいか
% ３．課題が始まった時刻（ waitkeyup が実行された時刻 ）
% 　　を Tstart という名前の変数に代入しよう
% ４．キーが何も押されなくても30秒経ったら始まる様に
% 　　するためにはどうすればよいか
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% 課題試行のメインループ
for i = 1:countdatarows % 課題試行のメインループを入力データファイルの行数分繰り返し
   
   %% 刺激単語の準備
   word = getdata( i, 1 ); % 入力ファイルの i 行 1 列目のデータを変数 word に読込み
   clearpict( 1 ); % スクリーンバッファ 1 の内容を消去しておく
   preparestring( word, 1 ); % スクリーンバッファ 1 に word に読込んだ単語刺激を書込み
   
   %% 固視点の表示と待機
   drawpict( 2 ); % 固視点が書かれているスクリーンバッファ 2 を画面に表示
   wait( 1500 ); % 固視点が表示された状態で 1500 ms 待機
   
   %% 刺激単語の表示と待機
   t0(i) = drawpict( 1 ); % 刺激単語が書かれているスクリーンバッファ 1 を画面に表示、
                       % その時刻を変数 t0 に代入
   clearkeys; % 刺激呈示までのキーボードバッファを消去しておく
   waituntil( t0(i) + 500 ); % 刺激呈示時刻 t0 から 500 ms 経過するまで待機
                          % （つまり、刺激が表示された状態で 500 ms 待機）
   
   %% 画面から刺激単語を消去
   drawpict( 3 ); % 何も書かれていないスクリーンバッファ 3 を画面に表示
                  % （つまり、刺激画面を消去）
   
   %% 反応時間窓の設定
   waituntil( t0(i) + 1000 ); % 刺激呈示時刻 t0 から 1000 ms 経過するまで待機
   
   %% 反応データ取得
   readkeys; % clearkeys以降のキーボードバッファを読込み
             % （つまり、刺激呈示直後からのキーボード情報の取得）
   
%% 演習７ キー入力 %%%%%%%%%%%%%%%%%%%%%%%%%
% １．getkeydownコマンドを使って、
% 　　押されたキーのIDを変数 K に、
% 　　キーが押された時刻を変数 TKD に、
% 　　キーが押された回数を変数 N に、
% 　　それぞれ代入しよう
%
     [ K, TKD, N ] = getkeydown;
%
% ２．プログラムを実行し、単語呈示直後にキーを押して
% 　　キーID、キー押し時刻、キー押し回数を確かめよう
%
% 　　ヒント：getkeydownコマンドの文末にセミコロン;を
% 　　　　　　付けないで実行し、コマンドウインドウ上に
% 　　　　　　毎回の結果を表示させる
%
% 　2回以上キーが押された場合には、何のキーがどの時刻に
% 　押されたか？
%  （キーIDの対応表は help readkeys を参照）
%
% ３．単語が表示されてから最初にキーが押されたときまで
% 　　の時間（反応時間）を変数 RT に代入するためには
%     どのようにすれば良いか？
%
%     さらに、最初に押されたキーのIDを変数 response に
%     代入しよう
%
%     ヒント：キー押しの回数 N をもとに場合分けする
%
     if N >= 1    % １回以上キーを押した（配列変数 TKD に１つ以上の要素）
         RT(i) = TKD( 1 ) - t0(i)    % 何を引けばよいか？
         response(i) = K( 1 )    % ( ) には何が入るか？
     elseif N == 0    % １回も押していない（TKD は空行列）
         RT(i) = NaN    % NaN は not a number (不定値）を表す
         response(i) = NaN
     end
     
     %'kekka1.txt'に結果を出力
     addresults(i, word, response(i), RT(i)); 

%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% 演習８ 出力ファイル %%%%%%%%%%%%%%%%%%%%%
% ０．start_cogentの前にconfig_resultsを記入、
% 　　結果出力ファイルを 'kekka1.txt' に指定しよう
% 
% addresultsコマンドを使って、
% １．試行回数、単語呈示時刻、呈示単語名、
% 　　キー押しの回数、一回目のキー番号、反応時間
% 　　などを出力ファイルに書き出そう
%
%     addresults はプログラム内のどこに書くべきか？
%
% ２．書き出された出力ファイルをエディタで確認してみよう
%
% 配列変数を用いて、
% ３．各試行における 単語呈示時刻、最初に押されたキーID、
% 　　反応時間などを試行順に記録、
% 　　（ヒント： 各変数に ( i ) を付けて配列化する）
% ４．これら変数を 'kekka1.mat' に保存しよう
%
% clear all コマンドでワークスペースから消去した後に
% load コマンドを用いてワークスペースに再読込できるか？
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   
end % 試行のメインループの最後

%'kekka1.mat'に結果を出力
save('kekka1.mat', 't0', 'response', 'RT');

%% cogent toolboxの終了
stop_cogent; % cogent関数終了