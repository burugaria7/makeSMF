# makeSMF

Synthesia’s_Movie_To_SMF

目的	
Sythesiaのmidi動画を解析しSMF形式で書き出す

使用言語
扱える言語がc++かjavaなんだけどjavaはないかなぁ。なのでc++
GUIなんかしらん、CUIでいいだろ？


動作

動画解析　(C++版 OpenCVによる解析を予定)
		(https://cvtech.cc/)

			↓

SMF形式による書き出し (MIDIデータ作成・編集用ライブラリ『MIDIDataライブラリ』による書き出しと予定)
(https://openmidiproject.osdn.jp/)
(https://openmidiproject.osdn.jp/MIDIDataLibrary.html)


動画解析について
OpenCVにより指定フレームごとに画像化し解析する。
指定フレーム数は後々のSMF書き出しに使用する可能性あり？

画像解析の範囲について
まずはSynthesiaでAll88設定になってると過程
後々の実装でC4座標の指定や、自己解析による自動設定などの可能性
追記：最近のSynthesiaだとC4などの表記がうっすらある。
	昔のものだとないのである場合は自動設定でもいいかも

追記：http://opencv.jp/sample/simple_gui.html
	この辺使って画像表示して例えばC4とその+1をクリックして
	その座標から設定するのありなのでは、精度高そう

プログラムの大まかな流れ
準備段階として画像の初期状態(一枚目の画像から？)にて各音程の座標を設定する（All88固定の場合はコード上で設定して置く？）
	↓
次の画像を読み込み、色が白または黒ではない座標を検知し、その座標によってSFMイベントに関する関数を呼ぶ。
		(ここの処理を一度に行ってるけど、デバッグなどのことを考えると、　　　　　　一度配列に保存して、後に書き出しを行ったほうが良いかもしれない)
　時間設定について
SMFイベント登録の際の時間設定は、

要再考
time(s) = n(n枚目の画像)* (任意分割フレーム数) /fps(動画のフレーム)


クラス分け
