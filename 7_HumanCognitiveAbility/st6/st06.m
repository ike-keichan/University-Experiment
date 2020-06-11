%Keisuke Ikeda%
%744069%

%% 課題プログラムの初期設定
config_display(0, 4, [0 0 0], [1 1 0], 'ゴシック', 50, 4, 0) % スクリーンをウインドウモードに初期設定、その他はデフォルト設定
config_data( 'st06_dat.txt' ); % 入力データファイルを st06.dat に設定
config_results('st06_res.txt'); % 出力データファイルを st06.res に設定
config_keyboard; % キーボードの初期設定
 
%% cogent toolboxの起動
start_cogent; % cogent関数起動（スクリーン、タイマー、キーボードバッファなど）

%ゴシック体, 25px
settextstyle( 'ゴシック', 25);

%% 固視点の準備
preparestring( '・', 2 ); % スクリーンバッファ 2 に固視点（・）を書込み

%フォント色：青色
setforecolour( 0, 0, 1); 

%ゴシック体, 120px
%settextstyle( 'ゴシック', 120);
 
%% 課題試行のメインループ
for i = 1:countdatarows % 課題試行のメインループを入力データファイルの行数分繰り返し
   
   %% 刺激単語の準備
   word = getdata( i, 1 ); % 入力ファイルの i 行 1 列目のデータを変数 word に読込み
      
   %% 画面に刺激単語を書き込み
   clearpict( 1 ); % スクリーンバッファ 1 の内容を消去しておく
   preparestring( word, 1 ); % スクリーンバッファ 1 に word に読込んだ単語刺激を書込み
   
   %% 固視点の表示と待機
   drawpict( 2 ); % 固視点が書かれているスクリーンバッファ 2 を画面に表示
   wait( 300 ); % 固視点が表示された状態で 300 ms 待機
   
   %% 刺激単語の表示
   drawpict( 1 ); % 刺激単語が書かれているスクリーンバッファ 1 を画面に表示
   
   %% 刺激単語の待機
   t0 = time; % 開始時間
   
   %% キーボードバッファの消去
   clearkeys; % 刺激呈示までのキーボードバッファを消去しておく
   
   %% 刺激単語の待機
   waituntil( t0 + 550 ); % 刺激呈示時刻 t0 から 550 ms 経過するまで待機
   
   %% 画面から刺激単語を消去
   drawpict( 3 ); % 何も書かれていないスクリーンバッファ 3 を画面に表示
   waituntil( t0 + 1000 ); % 刺激呈示時刻 t0 から 1000 ms 経過するまで待機
   
   %% 反応データ取得
   readkeys; % clearkeys以降のキーボードバッファを読込み
      
   %% キーボードバッファの取得
   [ key, t, n ] = getkeydown; % readkeys で読み込んだキーボードバッファの内容から変数に代入
                               % 押されたキーのID：key キーを押した時間：t、　キーを押した回数：n
   
   %% 反応データの場合分け
   if n == 0 % １回もキーを押していない
      responce(i) = 0; % 反応回数responceを0回にする。
      rt(i) = 0; % 反応時間rt(i)をを0秒にする。
   elseif n == 1 % １回キーを押した
      responce(i) = key(1); % 反応回数responceを1回にする。
      rt(i) = t(1) - t0; % 反応時間rt(i)を計算して代入する。
   else %１回以上キーを押した
      responce(i) = 0; % 反応回数responceを0回にする。
      rt(i) = 0; % 反応時間rt(i)をを0秒にする。
   end
   
   %%  ｓｔ０６.res に結果を出力
   addresults(i, word, responce(i), rt(i) ); % 記憶した反応データのファイル出力
 
end % 試行のメインループの最後

%'st06_mat.mat'に結果を出力
save('st06_res.mat', 't0', 'responce', 'rt');
 
%% cogent toolboxの終了
stop_cogent; % cogent関数終了

