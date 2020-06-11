%Keisuke Ikeda%
%744069%

%%初期化
clear all

%% 課題プログラムの初期設定
config_display(0, 4, [0 0 0], [0 0 1], 'ゴシック', 50, 4, 0) % スクリーンをウインドウモードに初期設定、その他はデフォルト設定
config_results('myExperiment_res.txt'); % 出力データファイルを myExperiment_res.txt に設定
config_keyboard; % キーボードの初期設定
 
%%変数の定義
%actionNumber = ['①', '②', '③', '④', '⑤', '⑥', '⑦', '⑧', '⑨']; % 各位置の割り当て数字を定義する。
xPosition = [-320, 0, 320, -320, 0, 320, -320,0, 320  ]; % 文字を書き込むx座標を定義する。
yPosition = [256, 256, 256, 0, 0, 0, -256, -256, -256]; % 文字を書き込むy座標を定義する。

%% cogent toolboxの起動
start_cogent; % cogent関数起動（スクリーン、タイマー、キーボードバッファなど）

%% 固視点の準備
preparestring( '・' , 2 ); % スクリーンバッファ 2 に固視点（・）を書込み
 
%% 課題試行のメインループ
for i = 1:30 % 課題試行のメインループを試行回数分繰り返し
    
    preparestring( i + 1 + '回目' ,2, 0, -256); % スクリーンバッファ 2 に固視点（・）を書込み
   
   %% 刺激部分の準備
  random = randi([1, 9]); % 刺激部分がランダムになるように変数を定義する。
      
   %% 画面に刺激部分を書き込み
   clearpict( 1 ); % スクリーンバッファ 1 の内容を消去しておく
   for j = 1:9
       if j == random
           preparestring( 'ス', 1,  xPosition(j), yPosition(j)); % スクリーンバッファ 1 に 読込んだ刺激部分を書込み
       else
           preparestring( 'ヌ', 1,  xPosition(j), yPosition(j)); % スクリーンバッファ 1 に 読込んだ部分を書込み
       end
   end
   
   %% 固視点の表示と待機
   drawpict( 2 ); % 固視点が書かれているスクリーンバッファ 2 を画面に表示
   wait( 500 ); % 固視点が表示された状態で 500 ms 待機
   
   %% 刺激部分の表示
   drawpict( 1 ); % 刺激部分が書かれているスクリーンバッファ 1 を画面に表示
   
   %% 刺激部分の待機
   t0 = time; % 開始時間
   
   %% キーボードバッファの消去
   clearkeys; % 刺激呈示までのキーボードバッファを消去しておく
   
   %% 刺激部分の待機
   waituntil( t0 + 2000 ); % 刺激呈示時刻 t0 から 1000 ms 経過するまで待機
   
   %% 画面から刺激部分を消去
   drawpict( 3 ); % 何も書かれていないスクリーンバッファ 3 を画面に表示
   waituntil( t0 + 1500 ); % 刺激呈示時刻 t0 から 1500 ms 経過するまで待機
   
   %% 反応データ取得
   readkeys; % clearkeys以降のキーボードバッファを読込み
      
   %% キーボードバッファの取得
   [ key, t, n ] = getkeydown; % readkeys で読み込んだキーボードバッファの内容から変数に代入
                               % 押されたキーのID：key キーを押した時間：t、　キーを押した回数：n
   
   %% 反応データの場合分け
   if n == 0 % １回もキーを押していない
      responce(i) = nan; % 反応回数responceをnanにする。
      RT(i) = nan; % 反応時間RT(i)ををnanにする。
   else % １回以上キーを押した
      responce(i) = key(1); % 反応回数responceを1回にする。
      RT(i) = t(1) - t0; % 反応時間RT(i)を計算して代入する。
   end
   
   randomMemory(i) = random;
   
   %%  myExperiment_res.txt に結果を出力
   addresults(i, randomMemory(i), responce(i), RT(i)); % 記憶した反応データのファイル出力
 
end % 試行のメインループの最後

%'myExperiment_res.mat'に結果を出力
save('myExperiment_res.mat', 'randomMemory', 'responce', 'RT', 't0');
 
%% cogent toolboxの終了
stop_cogent; % cogent関数終了

