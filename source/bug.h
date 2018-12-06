/******************************************************************************
    バグベアード -bugbeard-
        バグベアードヘッダファイル
                                            Coded by Wraith in Feb 23, 2003.
******************************************************************************/

///////////////////////////////////////////////////////////////////////////////
//
//  □ リポジトリ
//      https://github.com/wraith13/bugbeard
//
//  □ ライセンス情報
//      https://github.com/wraith13/bugbeard/blob/master/LICENSE_1_0.txt
//

#if !defined(BUGBEARD_BUG_H)

#define BUGBEARD_BUG_H


#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable:4456)
#endif


///////////////////////////////////////////////////////////////////////////////
//
//  動作確認済みコンパイラ
//

//  ・Borland C++ 5.5.1 以降
//  ・Visual C++ 6.0 以降
//  ・Intel C++ Compiler
//  ・GNC C++ Compiler
//  ・Metrowerks C/C++ Compiler 2.4 以降
//  ・Open Watcom C/C++ 1.5 以降


///////////////////////////////////////////////////////////////////////////////
//
//  defines
//

//
//  ☆使用言語指定マクロ
//

//  コンパイル時に指定するのが面倒な場合は以下のコメント行から適切な指定を
//  (コメントを解除して)有効にしてください。指定がない場合はデフォルトで日
//  本語が使用されます。
//
//#define BUG_LANG_JP   //  日本語
//#define BUG_LANG_EN   //  English

#if !(defined(BUG_LANG_JP) || defined(BUG_LANG_EN))
#   define BUG_LANG_JP
#endif


//
//  ☆文字型指定マクロ
//

//  このモジュールで使用する文字型を指定します。BUG_USE_CHAR もしくは
//  BUG_USE_WCHAR を定義してください。
//
//  どちらも指定されていない場合は _UNICODE, UNICODE マクロを元に自動判別定義
//  されます。
//
//  コンパイル時に指定するのが面倒な場合は以下のコメント行のどちらかを(コメン
//  トを解除して)有効にしてください。
//
//#define BUG_USE_CHAR
//#define BUG_USE_WCHAR

#if !defined(BUG_USE_CHAR) && !defined(BUG_USE_WCHAR)
#   if defined(_UNICODE) || defined(UNICODE)
#       define BUG_USE_WCHAR
#   else
#       define BUG_USE_CHAR
#   endif
#endif


//
//  ☆プロセスモデル指定マクロ
//

//  マルチプロセスとしてアプリケーションが同時に複数インスタンス稼働する場合
//  に BUG_MULTI_PROCESS マクロを定義してください。ログ出力の内容にプロセスID
//  が伴うようになりどのプロセスのログか識別したりビューアでフィルターを噛ま
//  せて特定のプロセスのログだけ抽出したりできるようになります。
//
//  コンパイル時に指定するのが面倒な場合は以下のコメント行のどちらかを(コメン
//  トを解除して)有効にしてください。
//
//#define BUG_SINGLE_PROCESS
//#define BUG_MULTI_PROCESS

#if !defined(BUG_SINGLE_PROCESS) && !defined(BUG_MULTI_PROCESS)
#   define BUG_SINGLE_PROCESS
#endif


//
//  ☆スレッドモデル指定マクロ
//

//  このモジュールをシングルスレッドで利用するのか、あるいはマルチスレッドで
//  利用するのかを指定します。
//
//  どちらも指定されていない場合は _MT, __MT__ マクロを元に自動判別定義
//  されます。
//
//  コンパイル時に指定するのが面倒な場合は以下のコメント行のどちらかを(コメン
//  トを解除して)有効にしてください。
//
//#define BUG_SINGLE_THREAD
//#define BUG_MULTI_THREAD

#if !defined(BUG_SINGLE_THREAD) && !defined(BUG_MULTI_THREAD)
#   if defined(_MT) || defined(__MT__)
#       define BUG_MULTI_THREAD
#   else
#       define BUG_SINGLE_THREAD
#   endif
#endif


//
//  ☆スレッドローカルストレージ修飾指定マクロ
//

//  このモジュールをマルチスレッドで利用する際に処理系組み込みのスレッド
//  ローカルストレージ機能を利用したい場合に指定します。
//
//  このマクロが定義されていなければ Windows API もしくは pthread を利用
//  してスレッドローカルストレージを使用します。
//
//  コンパイル時に指定するのが面倒な場合は以下のコメント行のどちらかを(コメン
//  トを解除して)有効にしてください。
//
//  for vc
//#define BUG_THREAD_LOCAL_STORAGE(type) __declspec(thread) type
//  for gcc
//#define BUG_THREAD_LOCAL_STORAGE(type) __thread type

#if defined(BUG_SINGLE_THREAD) && !defined(BUG_THREAD_LOCAL_STORAGE)
#   define BUG_THREAD_LOCAL_STORAGE(type) type
#endif


//
//  ☆ロケーション情報除外指定マクロ
//

//  このマクロが定義されているとログ出力にロケーション情報(__FILE__ 及び 
//  __LINE__)が含まれなくなります。
//
//  コンパイル時に指定するのが面倒な場合は以下のコメント行(コメントを解除
//  して)有効にしてください。
//
//#define BUG_WITHOUT_LOCATION_INFO


//
//  ☆ソースコード隠蔽指定マクロ
//

//  このマクロが定義されているとステートメントハックによるログ出力中の条件
//  式が "..." に置き換えられます。
//
//  コンパイル時に指定するのが面倒な場合は以下のコメント行(コメントを解除
//  して)有効にしてください。
//
//#define BUG_MASK_SOURCECODE

#if defined(BUG_MASK_SOURCECODE)
#define BUG_MASK_TARGET(X)     "..."
#else
#define BUG_MASK_TARGET(X)     X
#endif


//
//  ☆関数名取得組み込みマクロ指定マクロ
//

//  処理系で定義されている関数名取得組み込みマクロがある場合に指定します。
//  g++ では自動で __PRETTY_FUNCTION__ として定義されます。
//
//  このマクロが有効だとログ出力量が大幅に増えることになります。自動定義
//  を回避したい場合は BUG_NO_FUNCTION_NAME マクロを定義してください。
//
//  コンパイル時に指定するのが面倒な場合は以下のコメント行のどちらかを(コメン
//  トを解除して)有効にしてください。
//
//#define BUG_FUNCTION_NAME 関数名取得マクロ
//#define BUG_NO_FUNCTION_NAME

#if !defined(BUG_FUNCTION_NAME) && !defined(BUG_NO_FUNCTION_NAME)
#   if defined(__GNUC__)
#       define BUG_FUNCTION_NAME __PRETTY_FUNCTION__
#   endif
#endif


//
//  ☆実装拒否指定マクロ
//

//  コンパイル時に指定するのが面倒な場合は以下のコメント行を
//  (コメントを解除して)有効にしてください。
//
//#define   BUG_DISABLE_BUGBEARD


//
//  ☆グローバルロガー定義マクロ
//

//  このマクロはシンタックスシュガー的なもので、このマクロでグローバルな
//  ロガーの定義を指定おくとこのヘッダーファイル内で定義が行われます。
//  このマクロを利用することでロガーを定義する際にこのヘッダーファイル
//  を２度インクルードすることを回避できます。
//  
//#define BUG_DEFINE_GLOBAL_LOGGER    new bugbeard::bug_tree_logger(new bugbeard::bug_file_writer("trace.log"))


//
//  ☆グローバルプロファイラ定義マクロ
//

//  このマクロはシンタックスシュガー的なもので、このマクロでグローバルな
//  プロファイラの定義を指定おくとこのヘッダーファイル内で定義が行われます。
//  このマクロを利用することでプロファイラを定義する際にこのヘッダーファイル
//  を２度インクルードすることを回避できます。
//  
//#define BUG_DEFINE_GLOBAL_PROFILER  new bugbeard::bug_tsv_profiler(new bugbeard::bug_file_writer("profile.tsv"), new bugbeard::bug_file_writer("coverage.tsv"))


//
//  ☆.tsv ログヘッダー出力拒否指定マクロ
//

//  このマクロが定義されていると .tsv ログのヘッダー行を出力しなくなります。
//
//  コンパイル時に指定するのが面倒な場合は以下のコメント行(コメントを解除
//  して)有効にしてください。
//
//#define BUG_WITHOUT_TSV_LOG_HEADER


//
//  ☆.tsv プロファイルデータヘッダー出力拒否指定マクロ
//

//  このマクロが定義されていると .tsv プロファイルデータのヘッダー行を出力
//  しなくなります。
//
//  コンパイル時に指定するのが面倒な場合は以下のコメント行(コメントを解除
//  して)有効にしてください。
//
//#define BUG_WITHOUT_TSV_PROFILE_HEADER


//
//  ☆.tsv カバレッジデータヘッダー出力拒否指定マクロ
//

//  このマクロが定義されていると .tsv カバレッジデータのヘッダー行を出力
//  しなくなります。
//
//  コンパイル時に指定するのが面倒な場合は以下のコメント行(コメントを解除
//  して)有効にしてください。
//
//#define BUG_WITHOUT_TSV_COVERAGE_HEADER


//
//  ☆.tsv コールグラフデータヘッダー出力拒否指定マクロ
//

//  このマクロが定義されていると .tsv コールグラフデータのヘッダー行を出力
//  しなくなります。
//
//  コンパイル時に指定するのが面倒な場合は以下のコメント行(コメントを解除
//  して)有効にしてください。
//
//#define BUG_WITHOUT_TSV_CALLGRAPH_HEADER


//
//  ☆プロファイル計算方式指定マクロ
//

//  再帰的関数呼び出しが行われた場合の [合計総稼働時間],[合計総バグ時間],
//  [合計総実働時間],[合計子稼働時間],[合計子バグ時間],[合計子実働時間] の
//  計算方法を指定します。([合計自稼働時間],[合計自バグ時間],[合計自実働時間] 
//  はこの指定の影響を受けません。)
//
//  # 合計から平均を計算する為、 [平均総稼働時間],[平均総バグ時間],
//  # [平均総実働時間],[平均子稼働時間],[平均子バグ時間],[平均子実働時間] も
//  # 影響を受けます。
//
//  BUG_SMART_PROFILE を指定した場合、[合計総*時間], [合計子*時間] に再帰的
//  関数呼び出しが行われた場合に重複して時間が加算されることはなく、必ず
//  @OVERALL_SCOPE の同項目以下の時間に収まり直感的に理解しやすく且つチュー
//  ニングの目安として望ましい時間となります。
//
//  BUG_STRICT_PROFILE を指定した場合、再帰的関数呼び出しが行われた場合でも
//  特別扱いはせずに [合計総*時間], [合計子*時間] に通常の関数呼び出しと同様
//  に加算します。この為、 @OVERALL_SCOPE の同項目を超えるようなケースも存在
//  し、直感的には一見おかしな値に見えますが、厳密にはむしろこちらのほうが理
//  屈的に正しい値であると言えます。
//
//  次の二つのコールスタックとその所要時間の例を考えてみてください。
//
//     例１： @OVERALL_SCOPE(3秒) → A1(3秒) → B1(2秒) → C1(1秒)
//     例２： @OVERALL_SCOPE(3秒) → A2(3秒) → A2(2秒) → A2(1秒)
//
//  ...のようになる場合、例１のプロファイリングの結果は...
//
//     BUG_SMART_PROFILE:
//         @OVERALL_SCOPE: 合計総時間:3秒 == 合計自時間:0秒 + 合計子時間:3秒
//         A1:             合計総時間:3秒 == 合計自時間:1秒 + 合計子時間:2秒
//         B1:             合計総時間:2秒 == 合計自時間:1秒 + 合計子時間:1秒
//         C1:             合計総時間:1秒 == 合計自時間:1秒 + 合計子時間:0秒
//
//     BUG_STRICT_PROFILE:
//         @OVERALL_SCOPE: 合計総時間:3秒 == 合計自時間:0秒 + 合計子時間:3秒
//         A1:             合計総時間:3秒 == 合計自時間:1秒 + 合計子時間:2秒
//         B1:             合計総時間:2秒 == 合計自時間:1秒 + 合計子時間:1秒
//         C1:             合計総時間:1秒 == 合計自時間:1秒 + 合計子時間:0秒
//
//  ...のようになり内容は変わりませんが、例２のプロファイリングの結果は...
//
//     BUG_SMART_PROFILE:
//         @OVERALL_SCOPE: 合計総時間:3秒 == 合計自時間:0秒 + 合計子時間:3秒
//         A2:             合計総時間:3秒 == 合計自時間:3秒 + 合計子時間:0秒
//
//     BUG_STRICT_PROFILE:
//         @OVERALL_SCOPE: 合計総時間:3秒 == 合計自時間:0秒 + 合計子時間:3秒
//         A2:             合計総時間:6秒 == 合計自時間:3秒 + 合計子時間:3秒
//
//  ...のようになり大きく変わります。先述したように BUG_SMART_PROFILE のほう
//  が直感的に正しく且つ分かりやすい値となっており、一方で BUG_STRICT_PROFILE 
//  のほうは A2 の各計測時間が例１の A1, B1, C1 の合計と等しく厳密にはこちら
//  の値こそが正しいと言えるでしょう。
//
//  理屈的には BUG_STRICT_PROFILE の計算方法が正しいのですが、プロファイリング
//  機能はとしての目的を考えると BUG_STRICT_PROFILE の計算方法では紛らわしい為 
//  BUG_SMART_PROFILE をデフォルトとしています。しかし、 BUG_STRICT_PROFILE で
//  ないと計測上辻褄合わせができなくなる場面も考えられますので、状況に応じて
//  適切な方を指定してください。
//
//  コンパイル時に指定するのが面倒な場合は以下のコメント行のどちらかを(コメン
//  トを解除して)有効にしてください。
//
//#define BUG_SMART_PROFILE
//#define BUG_STRICT_PROFILE

#if !defined(BUG_SMART_PROFILE) && !defined(BUG_STRICT_PROFILE)
#   define BUG_SMART_PROFILE
#endif


//
//  ☆プロファイルデータ出力カラム指定マクロ
//

//  ....
//
//#define BUG_PROFILE_OUTPUT_FULL_DATA
//#define BUG_PROFILE_OUTPUT_CORE_DATA

#if !defined(BUG_PROFILE_OUTPUT_FULL_DATA) && !defined(BUG_PROFILE_OUTPUT_CORE_DATA)
#   define BUG_PROFILE_OUTPUT_FULL_DATA
#endif


//
//  ☆C++11モード有効化指定マクロ
//

//  ....
//
//#define BUG_ENABLED_CPP11_OR_LATER

#if !defined(BUG_ENABLED_CPP11_OR_LATER)
#   if 201103L <= __cplusplus
#       define BUG_ENABLED_CPP11_OR_LATER
#   endif
#endif


//
//  ☆強制終了方法指定マクロ
//

//  timelimit violation 発生時のプログラムの停止方法を指定します。 

#if !defined(TRICKLIB_BUG_TIMELIMIT_EXIT)
#define TRICKLIB_BUG_TIMELIMIT_EXIT    exit(EXIT_FAILURE)
#endif


//  逆意定義

#if !defined(BUG_DISABLE_BUGBEARD)
#   if  !defined(BUG_LOAD_BUGBEARD)
#       define  BUG_LOAD_BUGBEARD
#   endif
#endif

//
//  ...
//

#define BUG_NOTHING         ((void)0)
#define BUG_ID(A, B)         BUG_ID_core(A, B)
#define BUG_ID_core(A, B)    A##B

//
//  ...
//

#if defined(BUG_USE_CHAR)
#   define BUG_CHAR_TYPE char
#   define BUG_LPTSTR LPSTR
#   define BUG_LPCTSTR LPCSTR
#   define BUG_T_CORE(X) X
#   define BUG_API_T(X) X##A
#else
#   define BUG_CHAR_TYPE wchar_t
#   define BUG_LPTSTR LPWSTR
#   define BUG_LPCTSTR LPCWSTR
#   define BUG_T_CORE(X) L##X
#   define BUG_API_T(X) X##W
#endif
#define BUG_T(X) BUG_T_CORE(X)


//
//  ...
//
#if !defined(BUG_TO_STRING)
#   define BUG_TO_STRING_CORE(X)   #X
#   define BUG_TO_STRING(X)        BUG_TO_STRING_CORE(X)
#endif


//
//  コンパイラ情報
//

#if !defined(BUG_COMPILER_NAME)
#   if  defined(__INTEL_COMPILER)
#       define  BUG_COMPILER_NAME           "Intel C/C++ Compiler"
#       define  BUG_COMPILER_VERSION_NUMBER __INTEL_COMPILER
#       define  BUG_COMPILER_VERSION        BUG_TO_STRING(BUG_COMPILER_VERSION_NUMBER)
#   elif    defined(__GNUC__)
#       define  BUG_COMPILER_NAME           "g++"
#       define  BUG_COMPILER_VERSION_NUMBER __GNUC__ *100 +__GNUC_MINOR__
#       define  BUG_COMPILER_VERSION        __VERSION__
#   elif    defined(__WATCOMC__)
#       define  BUG_COMPILER_NAME           "Open Watcom C/C++"
#       define  BUG_COMPILER_VERSION_NUMBER __WATCOMC__
#       define  BUG_COMPILER_VERSION        BUG_TO_STRING(BUG_COMPILER_VERSION_NUMBER)
#   elif    defined(__BORLANDC__)
#       define  BUG_COMPILER_NAME           "Borland C++"
#       define  BUG_COMPILER_VERSION_NUMBER __BORLANDC__
#       define  BUG_COMPILER_VERSION        BUG_TO_STRING(BUG_COMPILER_VERSION_NUMBER)
#   elif    defined(_MSC_VER)
#       define  BUG_COMPILER_NAME           "Visual C++"
#       define  BUG_COMPILER_VERSION_NUMBER _MSC_VER
#       define  BUG_COMPILER_VERSION        BUG_TO_STRING(BUG_COMPILER_VERSION_NUMBER)
#   elif    defined(__MWERKS__)
#       define  BUG_COMPILER_NAME           "Metrowerks C/C++ Compiler"
#       define  BUG_COMPILER_VERSION_NUMBER __MWERKS__
#       define  BUG_COMPILER_VERSION        BUG_TO_STRING(BUG_COMPILER_VERSION_NUMBER)
#   elif    defined(__DMC__)
#       define  BUG_COMPILER_NAME           "Digital Mars C++"
#       define  BUG_COMPILER_VERSION_NUMBER __DMC__
#       define  BUG_COMPILER_VERSION        BUG_TO_STRING(BUG_COMPILER_VERSION_NUMBER)
#   else
#       define  BUG_COMPILER_NAME           "Unknown Compiler"
#       define  BUG_COMPILER_VERSION_NUMBER 0
#       define  BUG_COMPILER_VERSION        "Unknown Version"
#   endif
#endif


///////////////////////////////////////////////////////////////////////////////
//
//  ...
//

#if defined(BUG_LOAD_BUGBEARD)


///////////////////////////////////////////////////////////////////////////////
//
//  EVIL CONTRACT
//

#if !defined(BUG_EVIL_CONTRACT)
#error Thy have to conclude evil contract. 汝、悪魔の契約を締結せよ。

//
//  ★バグベアードをご利用に当たっての注意事項
//

//  邪道な技術により構築されたバグベアードは邪悪で忌むべき存在です。またバグ
//  ベアードの肝であるステートメントハックにより、さながらナノマシンの如くバ
//  グベアードのコードはユーザプログラムを隅々まで侵食します。故にバグベアー
//  ドの利用にあたっては以下のような注意が必要となります。
//
//  ・規格違反
//　　バグベアードは「ステートメントのマクロでの置換」という最上級の規格違反
//　　を犯しています。これによりバグベアードを利用したプログラムはあらゆる 
//　　C++ コンパイラでの動作保証は得られなくなります。ただし、これはバグベ
//　　アードの「ステートメントハック」が有効になっている場合の話であり、バグ
//　　ベアードがロードされていない状態を含め「ステートメントハック」が無効に
//　　なっている場合はその限りではありません。そして通常、リリース版のプログ
//　　ラムではバグベアードをロードしないことをオススメします。
//
//  ・エラー情報の侵食
//　　ユーザプログラムを隅々まで侵食するバグベアードのログ出力コードの影響に
//　　より、エラー情報(Win32API の GetLastError()で得られるエラーコードやグ
//　　ローバル変数に保持されるC/C++標準ライブラリのエラーコード)が上書きされ
//　　てしまう可能性があります。前項と同様にこれはバグベアードをロードしてい
//　　る状態でのみ発生しうる問題であり、バグベアードをロードしていない状態で
//　　あればこの問題は発生しません。
//
//  ・構文の制限
//　　バグベアードのステートメントハックの実装の都合より...
//
//　　　if (int i = func) ...
//　　　switch(int i = func) ...
//　　　while(int i = func) ...
//
//　　...のような形でステートメントに属する丸カッコで囲まれた箇所で変数を定
//　　義することができません。また...
//　　
//　　　void func(...) throw(...);
//　　
//　　...のような例外仕様構文が一切使えません。ただし、for ステートメントに
//　　関してはこの例外となり for(int i = 0;... などとしても問題ありません。
//　　また、そもそもステートメントハックを適用しない箇所ではこの制限はありま
//　　せん。
//
//  ・動作不安定
//　　バグベアードはオブジェクトの破棄のタイミングや operator や template 等
//　　がコンパイラによって意図通りに適用されるかどうかに強く依存する為、こち
//　　らで動作確認を行っていないコンパイラではあまり意図通りに機能することを
//　　期待できませんし、動作確認を行っているコンパイラでもバージョンによって
//　　は意図通りに機能しないかもしれません。
//
//  ・出力ログの変形
//　　前項と同じく、バグベアードはオブジェクトの破棄のタイミングや operator 
//　　や template 等がコンパイラによって意図通りに適用されるかどうかに強く依
//　　存する為、必ずしもは理想的な形でログを出力できない為に同じソースからコ
//　　ンパイルされたプログラムの出力ログがコンパイラ及びそのバージョンの違い
//　　により変形してしまうことがあります。具体的には return ステートメントの
//　　ログ出力は return fucn(); のような場合、func() 関数の呼び出しが終了した
//　　段階で return ステートメントのログを出力するのが理想的ですが、そのよう
//　　な形で実装できない処理系では func(); 関数の呼び出しの前に return ステー
//　　トメントのログ出力が行われます。また別の例では switch ステートメントに
//　　対してはスコープ扱いでログを出力するのが理想的ですが、そのように実装で
//　　きない処理系では switch ステートメントがスコープ扱いされません。
//
//  ・過剰な警告(ある意味、真っ当な警告)
//　　バグベアードをロードしてコンパイルを行うとバグベアードを利用していなけ
//　　れば表示されることはないような警告が過剰に表示されることがあります。
//　　これは通常、無視して構いません。ただし、バグベアードをロードしていない
//　　時に表示される警告は通常通りに対処してください。
//
//  ・順序不安定
//　　シングルプロセス×シングルスレッドでバグベアードを利用する場合は関係な
//　　い話ですが、マルチプロセスもしくはマルチスレッドでバグベアードを利用す
//　　る場合、複数のプロセス/スレッドの各種処理のログは必ずしもそれらの処理が
//　　実行された順番とそのログ出力結果の順番が一致しないことがあります。これ
//　　はログに記録が残る処理が実行されてから実際にログ出力が行われるまでに一
//　　定時間ではないタイムラグがある為です。もちろんこれは異なるプロセス・ス
//　　レッド間での話であり、同一プロセス・スレッド上の処理が実行された順番と
//　　そのログ出力結果の順番は必ず一致します。
//
//  これらを踏まえてなお、悪魔の契約を締結するならばその意思表明として 
//  BUG_EVIL_CONTRACT マクロを定義してください。BUG_EVIL_CONTRACT はユーザプ
//  ログラム全体に非常に強力な影響を及ぼすバグベアードのセーフティを解除する
//  為のマクロです。契約締結の暁にはバグベアードはさまざまな恩恵と災いをあな
//  たにもたらすでしょう。


//
//  ☆バグベアードをご利用に当たってのヒント
//

//  ・バグがあった場所のログ出力の為の埋め込みは消さない。
//　　一度、なんらかのバグ追跡の為に埋め込んだログ出力用コードは基本的には全
//　　てソースコード上に残しておくことをオススメします。実際にバグがあった箇
//　　所の埋め込みは残しておくことを特に強くオススメします。バグというのは一
//　　度直したつもりでも修正が十分でなく完全に直ってなかったり、別のバグを埋
//　　め込んでしまったりというのもよくある話です。また、バグというのは特定箇
//　　所に集中する傾向もあります。この為、その時目的としていたバグの直しが完
//　　了した後も、バグ追跡の為に埋め込んだログ出力用コードは全てソースコード
//　　上に残しておくことをオススメします。
//　　ログ出力量が過剰になってしまう場合は条件ディレクティブを使って必要な時
//　　以外は無効にしておくのがよいでしょう。
//
//  ・三項演算子のかわりに if を使用する。
//　　通常であればむしろ三項演算子が適用できる場面であれば if の使用を控える
//　　といったことが推奨されるかもしれませんが、あえて if を使用することで、
//　　バグベアード(のステートメントハック)で条件の判定結果を簡単にログに残せ
//　　ます。
//　　
//  ・明記が不要な場合でも return を記述する。
//　　戻り型が void の関数やコンストラクタ、デストラクタでも return を記述し
//　　ておくとその分ログ出力が増え、バグ追跡に役立ちます。
//　　
//  ・フィルタ機能を利用する。
//　　マルチプロセス及びマルチスレッドによるログ出力を同じファイル等に対して
//　　行うと、特に tree 形式でのログ出力は追跡中のログが他のプロセス及び他の
//　　スレッドによる出力とごちゃ混ぜになって追跡し辛くなることがありますが、
//　　その場合は適宜そのログの表示に使ってるエディタもしくはビューアが有する
//　　フィルタ機能を使い、プロセスIDやスレッドIDで表示を絞り込むとよいでしょ
//　　う。
//　　
//　・デバッグ以外での利用。
//　　バグベアードには環境および処理系にあまり依存せずに使えるスマートポイン
//　　タ、スレッドローカルストレージ、ミューテックス等々さまざま機能を内包し
//　　ていますのでちょっとしたプログラムでそれらの機能を利用するのもよいでしょ
//　　う。
//　　
//　・Excel を *.tsv ログのビューアとして使用する場合は Excel2007 以降で。
//　　Excel2003 以前では 65,536 行までしか扱えない為、極小規模なプログラムの
//　　ログならどうにかなるかもしれませんが、かなり厳しいです。 Excel2007 以降
//　　であれば、1,048,576行まで扱えます。...それでもプログラムによっては全然
//　　足りないでしょうが。

#endif


///////////////////////////////////////////////////////////////////////////////
//
//  各種環境対応
//

#define BUG_DISABLED_WHILE_SCOPE    //  do-while 構文を使用しない場合に限りこの行をコメントしても大丈夫。
                                    //  ただし、コンパイラにも依存することなので注意。

#if defined(_MSC_VER) && _MSC_VER <= 1200
#   define BUG_DISABLED_SWITCH_SCOPE
#endif

#if defined(__BORLANDC__)
#   if !defined(BUG_DISABLED_WHILE_SCOPE)
#       define BUG_DISABLED_WHILE_SCOPE
#   endif
#   if __BORLANDC__ <= 0x551
#       if !defined(BUG_DISABLED_PSAPI)
#           define BUG_DISABLED_PSAPI
#       endif
#   endif
#   if __BORLANDC__ < 0x590
#       if !defined(BUG_DISABLED_THROW_SCOPE)
#           define BUG_DISABLED_THROW_SCOPE
#       endif
#   endif
#endif

#if defined(__WATCOMC__)
#   define BUG_DISABLED_SWITCH_SCOPE
#   if !defined(BUG_DISABLED_WHILE_SCOPE)
#       define BUG_DISABLED_WHILE_SCOPE
#   endif
#   define BUG_NEED_SWITCH_CAST
#   define BUG_NEED_WHILE_CAST
#endif

#if defined(__WIN32__) || defined(_WIN32)
#   define BUG_MS_WINDOWS
#endif

#if defined(BUG_MS_WINDOWS)
#   define BUG_FORM_I64 "I64"
#else
#   define BUG_FORM_I64 "ll"
#endif


///////////////////////////////////////////////////////////////////////////////
//
//  includes
//

#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

#include <string>
#include <vector>
#include <stack>
#include <map>
#include <iostream>
#include <fstream>

#if defined(BUG_MS_WINDOWS)
#   include <windows.h>
#   include <process.h>
#   if defined(_MSC_VER)
#       pragma comment(lib, "USER32.lib")
#       pragma comment(lib, "ADVAPI32.lib")
#       pragma comment(lib, "VERSION.lib")
#   endif
#   if 0x0500 <= WINVER && !defined(BUG_DISABLED_PSAPI)
#       include <psapi.h>
#       pragma comment(lib, "PSAPI.lib")
#   endif
#else
#   include <sys/time.h>
#   include <stdint.h>
#   if defined(BUG_MULTI_THREAD)
#       include <pthread.h>
#   endif
#endif

#if !defined(__MWERKS__)
#   include <sys/timeb.h>
#endif


///////////////////////////////////////////////////////////////////////////////
//
//  mkdir/_mkdir
//

#if defined(BUG_MS_WINDOWS)
namespace bugbeard
{
    inline int bug_mkdir(const char * dir) { return CreateDirectoryA(dir, NULL); }
    inline int bug_mkdir(const wchar_t * dir) { return CreateDirectoryW(dir, NULL); }
}
#elif defined(__MWERKS__)
#   include <stat.h>
namespace bugbeard
{
    inline int bug_mkdir(const char * dir) { return _mkdir(dir); }
}
#elif defined(__GNUC__)
#   include <sys/stat.h>
namespace bugbeard
{
    inline int bug_mkdir(const char * dir) { return mkdir(dir, S_IRWXU |S_IRWXG |S_IRWXO); }
}
#endif

#if defined(__BORLANDC__) && 0x520 < __BORLANDC__
#   pragma warn -8070   //  ※
#   pragma warn -8027
#endif


///////////////////////////////////////////////////////////////////////////////
//
//  vanish macros
//

#if defined(BUG_WITHOUT_LOCATION_INFO)
#   define BUG_MSG(X)           bugbeard::bug_message(X)
#elif defined(BUG_FUNCTION_NAME)
#   define BUG_MSG(X)           bugbeard::bug_message(BUG_T(__FILE__), __LINE__, BUG_T(BUG_FUNCTION_NAME), X)
#else
#   define BUG_MSG(X)           bugbeard::bug_message(BUG_T(__FILE__), __LINE__, X)
#endif
#   define BUG_LOG              bugbeard::bug_logger::get_instance()
#   define BUG_VAL(X)           bugbeard::bug_encode(X, BUG_T(BUG_TO_STRING(X)))
#   define BUG_FORM             bugbeard::bug_form
#   define BUG_puts(X)          bugbeard::bug_log_message(BUG_LOG, BUG_MSG(X))
#   define BUG_scope(X)         bugbeard::bug_scope BUG_ID(bugbeard_scope_temporary_object, __LINE__)(BUG_LOG, BUG_MSG(X))
#   define BUG_scope_with_timelimit(X,timelimit)  bugbeard::bug_scope_with_timelimit BUG_ID(bugbeard_scope_temporary_object, __LINE__)(BUG_LOG, BUG_MSG(X), timelimit)
#   define BUG_inline_scope(X)  bugbeard::bug_scope(BUG_LOG, BUG_MSG(X))
#   define BUG_inline_scope_with_timelimit(X,timelimit)  bugbeard::bug_scope_with_timelimit(BUG_LOG, BUG_MSG(X), timelimit)
#   define BUG_exec(X)          X
#   define BUG_define_logger(X) bugbeard::bug_thread_local_storage<bugbeard::bug_logger> bug_user_logger(X)
#   define BUG_define_profiler(X) \
                                bugbeard::bug_thread_local_storage<bugbeard::bug_profiler> bug_user_profiler(X)

///////////////////////////////////////////////////////////////////////////////
//
//  ●bugbeard
//
namespace bugbeard
{
    ///////////////////////////////////////////////////////////////////////////
    //
    //  types
    //
    
    typedef BUG_CHAR_TYPE bug_char;
    typedef std::basic_string<bug_char> bug_string;
#if defined(BUG_MS_WINDOWS)
    typedef signed __int64 bug_sint64_type;
    typedef unsigned __int64 bug_uint64_type;
#else
    typedef int64_t bug_sint64_type;
    typedef uint64_t bug_uint64_type;
#endif


    ///////////////////////////////////////////////////////////////////////////
    //
    //  statics
    //
    
    namespace bug_term
    {
        const bug_string empty              = BUG_T("");
#if defined(BUG_LANG_JP)
        const bug_string horizon_line       = BUG_T("─");
        const bug_string begin_prefix       = BUG_T("▽");
        const bug_string end_prefix         = BUG_T("△");
        const bug_string session_root       = BUG_T("bugbeard session root");
#endif  //  defined(BUG_LANG_JP)
#if defined(BUG_LANG_EN)
        const bug_string horizon_line       = BUG_T("-");
        const bug_string begin_prefix       = BUG_T("begin ");
        const bug_string end_prefix         = BUG_T("end   ");
        const bug_string session_root       = BUG_T("bugbeard session root");
#endif  //  defined(BUG_LANG_EN)
#if defined(BUG_FUNCTION_NAME)
        const bug_string location_format    = BUG_T("<%s>#%d@%s");
#else
        const bug_string location_format    = BUG_T("<%s>#%d");
#endif
        const bug_string unknown_location   = BUG_T("<?unknown?>#?");
#if defined(BUG_FUNCTION_NAME)
        const bug_string unknown_function   = BUG_T("unknown function");
#endif
        
#if defined(__GNUC__)
        const bug_string dir_separator      = BUG_T("/");
#else //    defined(__GNUC__)
        const bug_string dir_separator      = BUG_T("\\");
#endif  //  defined(__GNUC__)

#if defined(BUG_MS_WINDOWS)
        const bug_string return_code        = BUG_T("\r\n");
#elif defined(__APPLE__)
        const bug_string return_code        = BUG_T("\r");
#else
        const bug_string return_code        = BUG_T("\n");
#endif
        
#if defined(BUG_LANG_JP)
        const bug_char * const wday_names[] =
        {
            BUG_T("日"), BUG_T("月"), BUG_T("火"), BUG_T("水"), BUG_T("木"), BUG_T("金"), BUG_T("土")
        };
        const bug_string stamp_title        = BUG_T("日付＆時刻：");
#endif  //  defined(BUG_LANG_JP)
#if defined(BUG_LANG_EN)
        const bug_char * const wday_names[] =
        {
            BUG_T("Sunday"), BUG_T("Monday"), BUG_T("Tuesday"), BUG_T("Wednesday"), BUG_T("thursday"), BUG_T("Friday"), BUG_T("Saturday")
        };
        const bug_string stamp_title        = BUG_T("Date & Time: ");
#endif  //  defined(BUG_LANG_EN)

        const bug_string no_stamp_message   = BUG_T("no-stamp");
        
        const bug_string if_statement_term  = BUG_T("if (");
        const bug_string false_result_term  = BUG_T("false;");
        const bug_string true_result_term   = BUG_T("true;");
        inline const bug_string & bool_result_term(bool a)
        {
            return a ? true_result_term: false_result_term;
        }
        
        const bug_char * overall_scope_label
                                            = BUG_T("@OVERALL_SCOPE");
        
#if defined(BUG_LANG_JP)
        const bug_string process_id_label   = BUG_T("プロセスID");
        const bug_string thread_id_label    = BUG_T("スレッドID");
#endif  //  defined(BUG_LANG_JP)
#if defined(BUG_LANG_EN)
        const bug_string process_id_label   = BUG_T("ProcessID");
        const bug_string thread_id_label    = BUG_T("ThreadID");
#endif  //  defined(BUG_LANG_EN)
#if defined(BUG_LANG_JP)
        const bug_string level_label        = BUG_T("レベル");
#endif  //  defined(BUG_LANG_JP)
#if defined(BUG_LANG_EN)
        const bug_string level_label        = BUG_T("Level");
#endif  //  defined(BUG_LANG_EN)
        const bug_string file_label         = BUG_T("__FILE__");
        const bug_string line_label         = BUG_T("__LINE__");
        const bug_string function_label     = BUG_T("__function__");
#if defined(BUG_LANG_JP)
        const bug_string scope_label        = BUG_T("スコープ");
#endif  //  defined(BUG_LANG_JP)
#if defined(BUG_LANG_EN)
        const bug_string scope_label         = BUG_T("Scope");
#endif  //  defined(BUG_LANG_EN)
        
#if defined(BUG_LANG_JP)
        const bug_string cumulative_label   = BUG_T("延べ");
        const bug_string total_label        = BUG_T("合計");
        const bug_string average_label      = BUG_T("平均");
        const bug_string min_label          = BUG_T("最小");
        const bug_string max_label          = BUG_T("最大");
        const bug_string all_label          = BUG_T("総");
        const bug_string self_label         = BUG_T("自");
        const bug_string sub_label          = BUG_T("子");
        const bug_string whole_label        = BUG_T("稼働");
        const bug_string bug_label          = BUG_T("バグ");
        const bug_string work_label         = BUG_T("実働");
        const bug_string time_label         = BUG_T("時間");
        const bug_string call_count_label   = BUG_T("コールカウント");
        const bug_string time_stamp_label   = BUG_T("スタンプ");
#endif  //  defined(BUG_LANG_JP)
#if defined(BUG_LANG_EN)
        const bug_string cumulative_label   = BUG_T("Cumulative");
        const bug_string total_label        = BUG_T("Total");
        const bug_string average_label      = BUG_T("Average");
        const bug_string min_label          = BUG_T("Min");
        const bug_string max_label          = BUG_T("Max");
        const bug_string all_label          = BUG_T("All");
        const bug_string self_label         = BUG_T("Self");
        const bug_string sub_label          = BUG_T("Sub");
        const bug_string whole_label        = BUG_T("Whole");
        const bug_string bug_label          = BUG_T("Bug");
        const bug_string work_label         = BUG_T("Work");
        const bug_string time_label         = BUG_T("Time");
        const bug_string call_count_label   = BUG_T("CallCount");
        const bug_string time_stamp_label   = BUG_T("Stamp");
#endif  //  defined(BUG_LANG_EN)
#if defined(BUG_LANG_JP)
		const bug_string caller_label = BUG_T("呼び出し元");
		const bug_string callee_label = BUG_T("呼び出し先");
#endif  //  defined(BUG_LANG_JP)
#if defined(BUG_LANG_EN)
		const bug_string caller_label = BUG_T("Caller");
		const bug_string callee_label = BUG_T("Callee");
#endif  //  defined(BUG_LANG_EN)

        const bug_string whole_time_label   = whole_label +time_label;
        const bug_string bug_time_label     = bug_label +time_label;
        const bug_string work_time_label    = work_label +time_label;
        
        const bug_string all_whole_time_label   = all_label +whole_time_label;
        const bug_string all_bug_time_label     = all_label +bug_time_label;
        const bug_string all_work_time_label    = all_label +work_time_label;
        const bug_string self_whole_time_label  = self_label +whole_time_label;
        const bug_string self_bug_time_label    = self_label +bug_time_label;
        const bug_string self_work_time_label   = self_label +work_time_label;
        const bug_string sub_whole_time_label   = sub_label +whole_time_label;
        const bug_string sub_bug_time_label     = sub_label +bug_time_label;
        const bug_string sub_work_time_label    = sub_label +work_time_label;
        
        const bug_string cumulative_total_all_whole_time_label     = cumulative_label +total_label +all_whole_time_label;
        const bug_string cumulative_total_all_bug_time_label       = cumulative_label +total_label +all_bug_time_label;
        const bug_string cumulative_total_all_work_time_label      = cumulative_label +total_label +all_work_time_label;
        const bug_string total_all_whole_time_label     = total_label +all_whole_time_label;
        const bug_string total_all_bug_time_label       = total_label +all_bug_time_label;
        const bug_string total_all_work_time_label      = total_label +all_work_time_label;
        const bug_string total_self_whole_time_label    = total_label +self_whole_time_label;
        const bug_string total_self_bug_time_label      = total_label +self_bug_time_label;
        const bug_string total_self_work_time_label     = total_label +self_work_time_label;
        const bug_string cumulative_total_sub_whole_time_label     = cumulative_label +total_label +sub_whole_time_label;
        const bug_string cumulative_total_sub_bug_time_label       = cumulative_label +total_label +sub_bug_time_label;
        const bug_string cumulative_total_sub_work_time_label      = cumulative_label +total_label +sub_work_time_label;
        const bug_string total_sub_whole_time_label     = total_label +sub_whole_time_label;
        const bug_string total_sub_bug_time_label       = total_label +sub_bug_time_label;
        const bug_string total_sub_work_time_label      = total_label +sub_work_time_label;
        
        const bug_string average_all_whole_time_label   = average_label +all_whole_time_label;
        const bug_string average_all_bug_time_label     = average_label +all_bug_time_label;
        const bug_string average_all_work_time_label    = average_label +all_work_time_label;
        const bug_string average_self_whole_time_label  = average_label +self_whole_time_label;
        const bug_string average_self_bug_time_label    = average_label +self_bug_time_label;
        const bug_string average_self_work_time_label   = average_label +self_work_time_label;
        const bug_string average_sub_whole_time_label   = average_label +sub_whole_time_label;
        const bug_string average_sub_bug_time_label     = average_label +sub_bug_time_label;
        const bug_string average_sub_work_time_label    = average_label +sub_work_time_label;

        const bug_string min_time_stamp_label           = min_label +time_stamp_label;
        const bug_string min_all_whole_time_label       = min_label +all_whole_time_label;
        const bug_string min_all_bug_time_label         = min_label +all_bug_time_label;
        const bug_string min_all_work_time_label        = min_label +all_work_time_label;
        const bug_string min_self_whole_time_label      = min_label +self_whole_time_label;
        const bug_string min_self_bug_time_label        = min_label +self_bug_time_label;
        const bug_string min_self_work_time_label       = min_label +self_work_time_label;
        const bug_string min_sub_whole_time_label       = min_label +sub_whole_time_label;
        const bug_string min_sub_bug_time_label         = min_label +sub_bug_time_label;
        const bug_string min_sub_work_time_label        = min_label +sub_work_time_label;

        const bug_string max_time_stamp_label           = max_label +time_stamp_label;
        const bug_string max_all_whole_time_label       = max_label +all_whole_time_label;
        const bug_string max_all_bug_time_label         = max_label +all_bug_time_label;
        const bug_string max_all_work_time_label        = max_label +all_work_time_label;
        const bug_string max_self_whole_time_label      = max_label +self_whole_time_label;
        const bug_string max_self_bug_time_label        = max_label +self_bug_time_label;
        const bug_string max_self_work_time_label       = max_label +self_work_time_label;
        const bug_string max_sub_whole_time_label       = max_label +sub_whole_time_label;
        const bug_string max_sub_bug_time_label         = max_label +sub_bug_time_label;
        const bug_string max_sub_work_time_label        = max_label +sub_work_time_label;
    }


    //////////////////////////////////////////////////////////////////////////////
    //
    //  auto close
    //

    template<class T> class demi
    {
        public:
            T value;

            demi() {}
            demi(const T &X) :value(X) {}

            operator T& () { return value; }
            operator const T& () const { return value; }

            T * operator & () { return &value; }
            const T * operator & () const { return &value; }

            T & operator () () { return value; }
            const T & operator () () const { return value; }
    };

#define DECLARE_AUTO_CLOSE(name, type, param, init, close_command) \
class name :public demi<type> \
{ \
  public: \
    name(param) :demi<type>(init) { } \
    ~name() \
    { \
        close(); \
    } \
    void close() \
    { \
        if (value) \
        { \
            close_command; \
            value = NULL; \
        } \
    } \
};

#if defined(BUG_MS_WINDOWS)
    DECLARE_AUTO_CLOSE(AUTO_HANDLE, HANDLE, HANDLE X = NULL, X, INVALID_HANDLE_VALUE != value && (CloseHandle(value), false))
    DECLARE_AUTO_CLOSE(AUTO_MAPVIEW, LPVOID, LPVOID X = NULL, X, UnmapViewOfFile(value))

    //////////////////////////////////////////////////////////////////////////////
    //
    //  ファイルオープン(読み込み専用、自動クローズ)
    //

    class OpenReadFile :public AUTO_HANDLE
    {
      public:
        OpenReadFile(const char *filename)
            :AUTO_HANDLE(
                CreateFileA(
                    filename, GENERIC_READ,
                    FILE_SHARE_READ |FILE_SHARE_WRITE, NULL,
                    OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL)) { }
        OpenReadFile(const wchar_t *filename)
            :AUTO_HANDLE(
                CreateFileW(
                    filename, GENERIC_READ,
                    FILE_SHARE_READ |FILE_SHARE_WRITE, NULL,
                    OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL)) { }
    };
#endif // defined(BUG_MS_WINDOWS)


    //////////////////////////////////////////////////////////////////////////////
    //
    //  ハッシュ値の取得
    //

#if 0x0500 <= WINVER
    DECLARE_AUTO_CLOSE(AUTO_CRYPTPROV, HCRYPTPROV, HCRYPTPROV X = NULL, X, CryptReleaseContext(value, 0))
    DECLARE_AUTO_CLOSE(AUTO_CRYPTHASH, HCRYPTHASH, HCRYPTHASH X = NULL, X, CryptDestroyHash(value))
    inline DWORD CalcHash(ALG_ID algid, HANDLE stream, BYTE *buffer, DWORD buffer_size)
    {
        //
        //  準備
        //
        AUTO_CRYPTPROV  prov_handle = NULL;
        AUTO_CRYPTHASH  hash_handle = NULL;
        AUTO_HANDLE     file_mapping = NULL;
        LARGE_INTEGER   file_size;
        file_size.QuadPart = 0L;
        if
        (
            NULL == stream ||
            INVALID_HANDLE_VALUE == stream ||
            (
                !CryptAcquireContext(&prov_handle, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT) &&
                (
                    (DWORD)NTE_BAD_KEYSET != GetLastError() ||
                    !CryptAcquireContext(&prov_handle, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_NEWKEYSET)
                )
            ) ||
            !CryptCreateHash(prov_handle, algid, 0, 0, &hash_handle) ||
            !GetFileSizeEx(stream, &file_size) ||
            (
                0L < file_size.QuadPart &&
                NULL == (file_mapping.value = CreateFileMapping(stream, NULL, PAGE_READONLY, file_size.HighPart, file_size.LowPart, NULL))
            )
        )
        {
            //throw win32_error();
            return 0;
        }
        
        //
        //  pump
        //
        LARGE_INTEGER   file_pos;
        file_pos.QuadPart = 0L;
        __int64 rest_size = file_size.QuadPart;
        SYSTEM_INFO sys_info;
        GetSystemInfo(&sys_info);
        const DWORD pump_buffer_size = sys_info.dwAllocationGranularity;
        while(0 < rest_size)
        {
            __int64 data_size = ((__int64)pump_buffer_size <= rest_size) ? pump_buffer_size : rest_size;
            AUTO_MAPVIEW data;
            if
            (
                NULL == (LPVOID)(data.value = MapViewOfFile(file_mapping, FILE_MAP_READ, file_pos.HighPart, file_pos.LowPart, (SIZE_T)data_size)) ||
                FALSE == CryptHashData(hash_handle, (LPBYTE)(LPVOID)data, (DWORD)data_size, 0)
            )
            {
                //throw win32_error();
                return 0;
            }
            file_pos.QuadPart += data_size;
            rest_size -= data_size;
        }
        
        //
        //  ハッシュ値の取得
        //
        DWORD hash_size = buffer_size;
        if (FALSE == CryptGetHashParam(hash_handle, HP_HASHVAL, buffer, &hash_size, NULL))
        {
            //throw win32_error();
            return 0;
        }

        return hash_size;
    }
#endif // 0x0500 <= WINVER


    ///////////////////////////////////////////////////////////////////////////
    //
    //  string utilities
    //

    //
    //  form
    //
    
    template<unsigned int buffer_size = 1024>
    class bug_form_ex :public bug_string
    {
    public:
#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable:4512)
#endif
        class bug_form_string
        {
            const bug_char * const str;
        public:
            bug_form_string(const bug_char * a_str) :str(a_str) {}
            bug_form_string(const bug_string & a_str) :str(a_str.c_str()) {}
            operator const bug_char * () const { return str; }
        };
#if defined(_MSC_VER)
#   pragma warning(pop)
#endif

        bug_form_ex(const bug_form_string format, ...)
        {
            bug_char buffer[buffer_size];
            buffer[buffer_size-1] = 0;
            va_list marker;
            va_start(marker, format);
#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable:4996)
#endif
#if defined(BUG_USE_CHAR)
#if defined(__GNUC__)
            vsnprintf(buffer, buffer_size, format, marker);
#else
            _vsnprintf(buffer, buffer_size, format, marker);
#endif
#else
            _vsnwprintf(buffer, buffer_size, format, marker);
#endif
#if defined(_MSC_VER)
#   pragma warning(pop)
#endif
            va_end(marker);
            if (buffer[buffer_size-1])
            {
                buffer[buffer_size-4] = BUG_T('.');
                buffer[buffer_size-3] = BUG_T('.');
                buffer[buffer_size-2] = BUG_T('.');
                buffer[buffer_size-1] = 0;
            }
            bug_string::operator=(buffer);
        }
    };
    typedef bug_form_ex<>   bug_form;

    
    //
    //  binary prefix
    //
    
    inline const bug_string bug_binary_prefix(const bug_uint64_type a_value, const bug_char * base_unit = BUG_T(""))
    {
        //  cf. http://ja.wikipedia.org/wiki/二進接頭辞
        
        const bug_char * binary_prefix[] =
        {
            BUG_T(""),      //  
            BUG_T("Ki"),    //  キビ(=1024)
            BUG_T("Mi"),    //  メビ(=1024キビ)
            BUG_T("Gi"),    //  ギビ(=1024メビ)
            BUG_T("Ti"),    //  テビ(=1024ギビ)
            BUG_T("Pi"),    //  ペビ(=1024テビ)
            BUG_T("Ei"),    //  エクスビ(=1024ペビ)
            BUG_T("Zi"),    //  ゼビ(=1024エクスビ)
            BUG_T("Yi"),    //  ヨビ(=1024ゼビ)
        };  //  ↑引数が64ビットなんで実際に Zi や Yi が使われることはない。
        
        int unit_index = 0;
        bug_uint64_type major_value = a_value;
        while(100 *1024 <= major_value)
        {
            ++unit_index;
            major_value /= 1024;
        }
        if (major_value < 1024)
        {
            return bug_form(BUG_T("%d%s%s(%") BUG_T(BUG_FORM_I64) BUG_T("d)"), (unsigned int)major_value, binary_prefix[unit_index], base_unit, a_value);
        }
        else
        {
            ++unit_index;
            double float_major_value = ((double)(unsigned int)major_value) /((double)1024.0);
            if (100.0 <= float_major_value)
            {
                return bug_form(BUG_T("%3.0f%s%s(%") BUG_T(BUG_FORM_I64) BUG_T("d)"), float_major_value, binary_prefix[unit_index], base_unit, a_value);
            }
            else
            if (10.0 <= float_major_value)
            {
                return bug_form(BUG_T("%2.1f%s%s(%") BUG_T(BUG_FORM_I64) BUG_T("d)"), float_major_value, binary_prefix[unit_index], base_unit, a_value);
            }
            else
            {
                return bug_form(BUG_T("%1.2f%s%s(%") BUG_T(BUG_FORM_I64) BUG_T("d)"), float_major_value, binary_prefix[unit_index], base_unit, a_value);
            }
        }
    }
    
    
    //
    //  encode
    //
    
    inline const bug_string bug_hex_encode(const void * a_data, size_t a_size)
    {
        const bug_char * hex_table = BUG_T("0123456789ABCDEF");
        const unsigned char * data = (const unsigned char *)a_data;
        const unsigned char * data_end = data +a_size;
        const size_t buffer_size = 64;
        bug_char buffer[buffer_size];
        size_t i = 0;
        bug_string result;
        while(data < data_end)
        {
            buffer[i++] = hex_table[(*data)>>4];
            buffer[i++] = hex_table[(*data)&15];
            ++data;
            if (buffer_size == i)
            {
                result.append(buffer, i);
                i = 0;
            }
        }
        if (i)
        {
            result.append(buffer, i);
        }
        return result;
    }
    
    inline const bug_string bug_encode_value(const int & a)
    {
        return bug_form(BUG_T("%d(0x%8.8X)"), a, a);
    }
    inline const bug_string bug_encode_value(const double & a)
    {
        return bug_form(BUG_T("%f"), a);
    }
    inline const bug_string bug_encode_value(const bug_uint64_type & a)
    {
        return bug_binary_prefix(a);
    }
    inline const bug_string bug_encode_value(bug_char * a)
    {
        return bug_form(BUG_T("\"%s\""), a);
    }
    inline const bug_string bug_encode_value(const bug_char * a)
    {
        return bug_form(BUG_T("\"%s\""), a);
    }
    inline const bug_string bug_encode_value(const bug_string & a)
    {
        return bug_form(BUG_T("\"%s\""), a.c_str());
    }
    template<class T> inline const bug_string bug_encode_value(const T & a)
    {
        return BUG_T("HEX:") +bug_hex_encode(&a, sizeof(T));
    }
    template<class T> inline const bug_string bug_encode(const T & a, const bug_char * name)
    {
        return bug_form(BUG_T("%s(0x%8.8X) = %s"), name, &a, bug_encode_value(a).c_str());
    }
    
    
    //
    //  run string
    //
    
    inline const bug_string bug_run_string(int a_number, const bug_string & a_string)
    {
        bug_string result;
        result.reserve(a_number *a_string.size());
        for(int i = 0; i < a_number; ++i)
        {
            result += a_string;
        }
        return result;
    }
    

    ///////////////////////////////////////////////////////////////////////////
    //
    //  clock
    //
    
    class bug_clock
    {
    public:
        time_t total_sec;
        int year;
        int mon;
        int mday;
        int wday;
        int hour;
        int min;
        int sec;
        int milli;
#if !defined(BUG_MS_WINDOWS)
        int usec;
#endif
        
        bug_clock()
        {
#if !defined(BUG_MS_WINDOWS)
            struct timeval tv;
            gettimeofday(&tv, NULL);
            const struct tm * tblock = localtime(&(tv.tv_sec));
#elif defined(__MWERKS__)
            time_t now;
            time(&now);
            const struct tm * tblock = localtime(&now);
#else
#   if defined(_MSC_VER)
#       pragma warning(push)
#       pragma warning(disable:4996)
#   endif
            struct timeb now;
            ftime(&now);
            const struct tm * tblock = localtime(&now.time);
#   if defined(_MSC_VER)
#       pragma warning(pop)
#   endif
#endif

#if !defined(BUG_MS_WINDOWS)
            total_sec = tv.tv_sec;
#elif defined(__MWERKS__)
            total_sec = now;
#else
            total_sec = now.time;
#endif
            year = (tblock->tm_year < 70) ? tblock->tm_year +2000: tblock->tm_year +1900;
            mon = tblock->tm_mon +1;
            mday = tblock->tm_mday;
            wday = tblock->tm_wday;
            hour = tblock->tm_hour;
            min = tblock->tm_min;
            sec = tblock->tm_sec;
#if !defined(BUG_MS_WINDOWS)
            milli = tv.tv_usec /1000;
            usec = tv.tv_usec;
#elif defined(__MWERKS__)
            milli = 0;
#else
            milli = now.millitm;
#endif
        }
    };

    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  dir
    //
    
    class bug_dull_dir
    {
        bug_string dirname;
    public:
        typedef bug_dull_dir type_this;
        bug_dull_dir(const bug_string & a_dirname) :dirname(a_dirname) { }
        bug_dull_dir(const type_this & a) :dirname(a.dirname) { }
        const bug_dull_dir operator+(const bug_string & a_pathname) const
        {
            return dirname +bug_term::dir_separator +a_pathname;
        }
        operator const bug_char * () const
        {
            return dirname.c_str();
        }
#if !defined(__MWERKS__)
        operator const bug_string & () const
        {
            return dirname;
        }
#endif
    };
    class bug_dir
    {
        bug_string dirname;
    public:
        typedef bug_dir type_this;
        bug_dir(const bug_char * a_dirname) :dirname(a_dirname) { }
        bug_dir(const bug_string & a_dirname) :dirname(a_dirname) { }
        bug_dir(const bug_form::bug_form_string format, ...)
        {
            const unsigned int buffer_size =1024;
            bug_char buffer[buffer_size];
            va_list marker;
            va_start(marker, format);
#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable:4996)
#endif
#if defined(BUG_USE_CHAR)
#if defined(__GNUC__)
            vsnprintf(buffer, buffer_size, format, marker);
#else
            _vsnprintf(buffer, buffer_size, format, marker);
#endif
#else
            _vsnwprintf(buffer, buffer_size, format, marker);
#endif
#if defined(_MSC_VER)
#   pragma warning(pop)
#endif
            va_end(marker);
            dirname = buffer;
        }
        bug_dir(const type_this & a) :dirname(a.dirname) { }
        const bug_dir operator+(const bug_dir & a) const
        {
            bug_mkdir(dirname.c_str());
            return dirname +bug_term::dir_separator +a.dirname;
        }
#if !defined(__MWERKS__)
        const bug_dull_dir operator+(const bug_char * a_pathname) const
        {
            bug_mkdir(dirname.c_str());
            return dirname +bug_term::dir_separator +a_pathname;
        }
#endif
        const bug_dull_dir operator+(const bug_string & a_pathname) const
        {
            bug_mkdir(dirname.c_str());
            return dirname +bug_term::dir_separator +a_pathname;
        }
    };

    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  win32 utilities
    //
    
#if defined(BUG_MS_WINDOWS)
    inline const std::string bug_get_win32_err_msgA(DWORD error_code = GetLastError())
    {
        LPVOID  message_buffer;
        FormatMessageA
        (
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            NULL, error_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPSTR)&message_buffer, 0, NULL
        );
        const std::string result = (const char *)message_buffer;
        LocalFree(message_buffer);
        return result;
    }

    inline const std::wstring bug_get_win32_err_msgW(DWORD error_code = GetLastError())
    {
        LPVOID  message_buffer;
        FormatMessageW
        (
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            NULL, error_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPWSTR)&message_buffer, 0, NULL
        );
        const std::wstring result = (const wchar_t *)message_buffer;
        LocalFree(message_buffer);
        return result;
    }
#if defined(_UNICODE) || defined(UNICODE)
#define bug_get_win32_err_msg bug_get_win32_err_msgW
#else
#define bug_get_win32_err_msg bug_get_win32_err_msgA
#endif

    struct bug_langandcodepage
    {
        WORD wLanguage;
        WORD wCodePage;
    };
    struct bug_translation_set
    {
        bug_langandcodepage * body;
        UINT body_byte_size;
        size_t get_size()
        {
            return body_byte_size / sizeof(*body);
        }
        bug_langandcodepage & operator [] (size_t index)
        {
            return body[index];
        }
        const bug_langandcodepage & operator [] (size_t index) const
        {
            return body[index];
        }
    };
    class bug_file_version_info
    {
      private:
        BYTE * buffer;
      public:
        bug_file_version_info(const bug_char * dll_name)
        {
            buffer = NULL;
            DWORD dummy = 0;
            DWORD version_info_size = BUG_API_T(GetFileVersionInfoSize)((bug_char *)dll_name, & dummy);
            if(version_info_size)
            {
                buffer = new BYTE[version_info_size];
                BUG_API_T(GetFileVersionInfo)((bug_char *)dll_name, 0, version_info_size, buffer);

            }
        }
        ~bug_file_version_info()
        {
            delete [] buffer;
        }
        bool is_valid()
        {
            return NULL != buffer;
        }
        bool query_value(BUG_LPTSTR lpSubBlock, LPVOID *lplpBuffer, PUINT puLen)
        {
            return 0 != BUG_API_T(VerQueryValue)(buffer, lpSubBlock, lplpBuffer, puLen);
        }
        bool query_value_translation(bug_langandcodepage * * lpTranslate, PUINT translate_length)
        {
            return query_value(BUG_T("\\VarFileInfo\\Translation"), (LPVOID *)lpTranslate, translate_length);
        }
        bool query_value_translation(bug_translation_set * translation_set)
        {
            translation_set->body = NULL;
            translation_set->body_byte_size = 0;
            return query_value_translation(&(translation_set->body), &(translation_set->body_byte_size));
        }
        bool query_string_value(BUG_LPTSTR lpSubBlock, bug_string * value)
        {
            LPVOID lpBuffer = NULL;
            UINT uLen = 0;
            bool result = query_value(lpSubBlock, &lpBuffer, &uLen);
            if (result)
            {
                *value = bug_form(BUG_T("%*s"), uLen, lpBuffer);
            }
            return result;
        }
        bool query_value_string_file_info(const bug_langandcodepage & langandcodepage, const bug_char * param_name, bug_string * value)
        {
            return query_string_value
            (
                (bug_char *)
                (
                    bug_form
                    (
                        BUG_T("\\StringFileInfo\\%04x%04x\\%s"),
                        langandcodepage.wLanguage,
                        langandcodepage.wCodePage,
                        param_name
                    ).c_str()
                ),
                value
            );
        }
    };

    class bug_OSVERSIONINFO
#if 0x0500 <= WINVER
        :public OSVERSIONINFOEX
#else
        :public OSVERSIONINFO
#endif
    {
    public:
        bug_OSVERSIONINFO()
        {
            ZeroMemory(this, sizeof(*this));
            dwOSVersionInfoSize = sizeof(*this);
#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable:4996)
#endif
            if (0 == BUG_API_T(GetVersionEx)((BUG_API_T(OSVERSIONINFO)*)this))
            {
                dwOSVersionInfoSize = sizeof(BUG_API_T(OSVERSIONINFO));
                BUG_API_T(GetVersionEx)((BUG_API_T(OSVERSIONINFO)*)this);
            }
            
            //  http://msdn.microsoft.com/en-us/library/windows/desktop/dn302074(v=vs.85).aspx
            //  manifest で Windows 8.1 以降への対応を謳っていないと 6.2 でクリップされてしまう為、
            //  バージョンが 6.2 以降の場合 KERNEL32.DLL のバージョン番号をカンニングして上書きする。
            //
            //  この細工によって、実行形式ファイルの[プロパティ]から[互換性]タブの互換モードが
            //  指定されててもその環境本来のバージョンを返す事になります。
            //
            //  manifest で最新の Windows への対応が指定されている場合は不要な処理であり、上記の
            //  ような副作用もある為、必要に応じて BUG_DISABLED_CHEAT_GET_WINDOWS_VERSION を指定
            //  してこの処理を無効にしてください。
#if !defined(BUG_DISABLED_CHEAT_GET_WINDOWS_VERSION)
            //  manifest で宣言されてるより新しいバージョンの Windows では manifest で対応を宣言
            //  しているバージョンでクリップされると予想されるので Windows 8 以降のバージョン番号
            //  が返された場合、 KERNEL32.DLL のバージョン番号をカンニングして上書きする。
            if (is_windows_8_or_later()) {
                bug_file_version_info file_version_info(BUG_T("kernel32.dll"));
                if(file_version_info.is_valid())
                {
                    bug_translation_set translation_set;
                    file_version_info.query_value_translation(&translation_set);
                    
                    for(size_t i = 0, size = translation_set.get_size(); i < size; ++i)
                    {
                        bug_string file_version_raw_string;
                        if (file_version_info.query_value_string_file_info(translation_set[i], BUG_T("FileVersion"), &file_version_raw_string))
                        {
                            const bug_char * numbers = BUG_T("0123456789");
                            std::vector<int> file_version_elements;
                            size_t begin = 0, end = 0;
                            do
                            {
                                begin = file_version_raw_string.find_first_of(numbers, end);
                                if (begin == bug_string::npos)
                                {
                                    break;
                                }
                                end = file_version_raw_string.find_first_not_of(numbers, begin);
                                const bug_string current = file_version_raw_string.substr
                                (
                                    begin,
                                    end != bug_string::npos ? end -begin: end
                                );
#if defined(BUG_USE_CHAR)
                                file_version_elements.push_back(atoi(current.c_str()));
#else
                                std::string narrow_current;
                                for(bug_string::const_iterator i = current.begin(), end = current.end(); i != end; ++i)
                                {
                                    narrow_current.push_back(static_cast<char>(*i));
                                }
                                file_version_elements.push_back(atoi(narrow_current.c_str()));
#endif
                            }
                            while(end != bug_string::npos);
                            
                            if (3 <= file_version_elements.size())
                            {
                                dwMajorVersion = file_version_elements[0];
                                dwMinorVersion = file_version_elements[1];
                                dwBuildNumber = file_version_elements[2];
                            }
                        }
                    }
                }
            }
#endif
            
#if defined(_MSC_VER)
#   pragma warning(pop)
#endif
        }
        bool is_target_or_later(DWORD major_vesion, DWORD minor_version = 0) const
        {
            return (major_vesion == dwMajorVersion && minor_version <= dwMinorVersion) || major_vesion < dwMajorVersion;
        }
        bool is_windows_10_or_later() const
        {
            return is_target_or_later(10, 0);
        }
        bool is_windows_8_1_or_later() const
        {
            return is_target_or_later(6, 3);
        }
        bool is_windows_8_or_later() const
        {
            return is_target_or_later(6, 2);
        }
        bool is_windows_7_or_later() const
        {
            return is_target_or_later(6, 1);
        }
        bool is_windows_vista_or_later() const
        {
            return is_target_or_later(6, 0);
        }
        bool is_windows_xp_or_later() const
        {
            return is_target_or_later(5, 1);
        }
    };
    
#if 0x0500 <= WINVER
    inline const bug_string bug_get_winver(const bug_OSVERSIONINFO & osvi = bug_OSVERSIONINFO())
    {
        //  この関数は MSDN のサンプルコード "Getting the System Version" の新旧二つのバージョンを元に作成しています。
    
        bug_string result = BUG_T("unknown");

        typedef void (WINAPI * PGNSI)(LPSYSTEM_INFO);
        typedef BOOL (WINAPI * PGPI)(DWORD, DWORD, DWORD, DWORD, PDWORD);
        
        SYSTEM_INFO si;
        ZeroMemory(&si, sizeof(si));
        
        // Call GetNativeSystemInfo if supported or GetSystemInfo otherwise.

        PGNSI pGNSI = (PGNSI)GetProcAddress(GetModuleHandleA("kernel32.dll"), "GetNativeSystemInfo");
        if(NULL != pGNSI)
        {
            pGNSI(&si);
        }
        else
        {
            GetSystemInfo(&si);
        }
        
        switch (osvi.dwPlatformId)
        {
        // Test for the Windows NT product family.

        case VER_PLATFORM_WIN32_NT:

            // Test for the specific product.
            switch(osvi.dwMajorVersion)
            {
            case 6:
                if (0 == osvi.dwMinorVersion)
                {
                    if(osvi.wProductType == VER_NT_WORKSTATION)
                    {
                        result = BUG_T("Microsoft Windows Vista");
                    }
                    else
                    {
                        result = BUG_T("Windows Server 2008");
                    }
                }
                if (1 == osvi.dwMinorVersion)
                {
                    if(osvi.wProductType == VER_NT_WORKSTATION)
                    {
                        result = BUG_T("Microsoft Windows 7");
                    }
                    else
                    {
                        result = BUG_T("Windows Server 2008 R2");
                    }
                }
                if (2 == osvi.dwMinorVersion)
                {
                    if(osvi.wProductType == VER_NT_WORKSTATION)
                    {
                        result = BUG_T("Microsoft Windows 8");
                    }
                    else
                    {
                        result = BUG_T("Windows Server 2012");
                    }
                }
                if (3 == osvi.dwMinorVersion)
                {
                    if(osvi.wProductType == VER_NT_WORKSTATION)
                    {
                        result = BUG_T("Microsoft Windows 8.1");
                    }
                    else
                    {
                        result = BUG_T("Windows Server 2012 R2");
                    }
                }
                if (0 == osvi.dwMinorVersion || 1 == osvi.dwMinorVersion)
                {
                    PGPI pGPI = (PGPI) GetProcAddress(GetModuleHandleA("kernel32.dll"), "GetProductInfo");
                    DWORD dwType = 0;
                    pGPI(6, 0, 0, 0, &dwType);
                    switch( dwType )
                    {
                    case 0x00000000: // == PRODUCT_UNDEFINED:
                        break;
                    case 0x00000001: // == PRODUCT_ULTIMATE:
                        result += BUG_T(" Ultimate Edition");
                        break;
                    case 0x00000047: // == PRODUCT_ULTIMATE_E:
                        result += BUG_T(" Ultimate E Edition");
                        break;
                    case 0x0000001C: // == PRODUCT_ULTIMATE_N:
                        result += BUG_T(" Ultimate N Edition");
                        break;
                    case 0x00000030: // == PRODUCT_PROFESSIONAL:
                        result += BUG_T(" Professional Edition");
                        break;
                    case 0x00000045: // == PRODUCT_PROFESSIONAL_E:
                        result += BUG_T(" Professional E Edition");
                        break;
                    case 0x00000031: // == PRODUCT_PROFESSIONAL_N:
                        result += BUG_T(" Professional N Edition");
                        break;
                    case 0x00000002: // == PRODUCT_HOME_BASIC:
                        result += BUG_T(" Home Basic Edition");
                        break;
                    case 0x00000043: // == PRODUCT_HOME_BASIC_E:
                        result += BUG_T(" Home Basic Edition");
                        break;
                    case 0x00000005: // == PRODUCT_HOME_BASIC_N:
                        result += BUG_T(" Home Basic N Edition");
                        break;
                    case 0x00000003: // == PRODUCT_HOME_PREMIUM:
                        result += BUG_T(" Home Premium Edition");
                        break;
                    case 0x00000044: // == PRODUCT_HOME_PREMIUM_E:
                        result += BUG_T(" Home Premium Edition");
                        break;
                    case 0x0000001A: // == PRODUCT_HOME_PREMIUM_N:
                        result += BUG_T(" Home Premium Edition");
                        break;
                    case 0x0000002A: // == PRODUCT_HYPERV:
                        result += BUG_T(" Microsoft Hyper-V Server");
                        break;
                    case 0x0000001E: // == PRODUCT_MEDIUMBUSINESS_SERVER_MANAGEMENT:
                        result += BUG_T(" Windows Essential Business Server Management Server");
                        break;
                    case 0x00000020: // == PRODUCT_MEDIUMBUSINESS_SERVER_MESSAGING:
                        result += BUG_T(" Windows Essential Business Server Messaging Server");
                        break;
                    case 0x0000001F: // == PRODUCT_MEDIUMBUSINESS_SERVER_SECURITY:
                        result += BUG_T(" Windows Essential Business Server Security Server");
                        break;
                    case 0x00000004: // == PRODUCT_ENTERPRISE:
                        result += BUG_T(" Enterprise Edition");
                        break;
                    case 0x00000046: // == PRODUCT_ENTERPRISE_E:
                        result += BUG_T(" Enterprise E Edition");
                        break;
                    case 0x0000001B: // == PRODUCT_ENTERPRISE_N:
                        result += BUG_T(" Enterprise N Edition");
                        break;
                    case 0x00000006: // == PRODUCT_BUSINESS:
                        result += BUG_T(" Business Edition");
                        break;
                    case 0x00000010: // == PRODUCT_BUSINESS_N:
                        result += BUG_T(" Business N Edition");
                        break;
                    case 0x00000007: // == PRODUCT_STANDARD_SERVER:
                        result += BUG_T(" Standard Edition");
                        break;
                    case 0x0000000D: // == PRODUCT_STANDARD_SERVER_CORE:
                        result += BUG_T(" Standard Edition (core installation)");
                        break;
                    case 0x00000028: // == PRODUCT_STANDARD_SERVER_CORE_V:
                        result += BUG_T(" Standard Edition without Hyper-V (core installation)");
                        break;
                    case 0x00000024: // == PRODUCT_STANDARD_SERVER_V:
                        result += BUG_T(" Standard Edition without Hyper-V");
                        break;
                    case 0x00000008: // == PRODUCT_DATACENTER_SERVER:
                        result += BUG_T(" Datacenter Edition");
                        break;
                    case 0x0000000C: // == PRODUCT_DATACENTER_SERVER_CORE:
                        result += BUG_T(" Datacenter Edition (core installation)");
                        break;
                    case 0x00000027: // == PRODUCT_DATACENTER_SERVER_CORE_V:
                        result += BUG_T(" Datacenter Edition without Hyper-V (core installation)");
                        break;
                    case 0x00000025: // == PRODUCT_DATACENTER_SERVER_V:
                        result += BUG_T(" Datacenter Edition without Hyper-V");
                        break;
                    case 0x00000009: // == PRODUCT_SMALLBUSINESS_SERVER:
                        result += BUG_T(" Small Business Server" );
                        break;
                    case 0x0000000A: // == PRODUCT_ENTERPRISE_SERVER:
                        result += BUG_T(" Enterprise Edition");
                        break;
                    case 0x0000000E: // == PRODUCT_ENTERPRISE_SERVER_CORE:
                        result += BUG_T(" Enterprise Edition (core installation)");
                        break;
                    case 0x00000029: // == PRODUCT_ENTERPRISE_SERVER_CORE_V:
                        result += BUG_T(" Enterprise Edition without Hyper-V (core installation)");
                        break;
                    case 0x0000000F: // == PRODUCT_ENTERPRISE_SERVER_IA64:
                        result += BUG_T(" Enterprise Edition for Itanium-based Systems");
                        break;
                    case 0x00000026: // == PRODUCT_ENTERPRISE_SERVER_V:
                        result += BUG_T(" Enterprise Edition without Hyper-V");
                        break;
                    case 0x0000000B: // == PRODUCT_STARTER:
                        result += BUG_T(" Starter Edition");
                        break;
                    case 0x00000042: // == PRODUCT_STARTER_E:
                        result += BUG_T(" Starter E Edition");
                        break;
                    case 0x0000002F: // == PRODUCT_STARTER_N:
                        result += BUG_T(" Starter N Edition");
                        break;
                    case 0x00000011: // == PRODUCT_WEB_SERVER:
                        result += BUG_T(" Web Server Edition");
                        break;
                    case 0x0000001D: // == PRODUCT_WEB_SERVER_CORE:
                        result += BUG_T(" Web Server Edition (core installation)");
                        break;
                    case 0x00000012: // == PRODUCT_CLUSTER_SERVER:
                        result += BUG_T(" Cluster Server Edition");
                        break;
                    case 0x00000013: // == PRODUCT_HOME_SERVER:
                        result += BUG_T(" Home Server Edition");
                        break;
                    case 0x00000014: // == PRODUCT_STORAGE_EXPRESS_SERVER:
                        result += BUG_T(" Storage Express Server Edition");
                        break;
                    case 0x00000015: // == PRODUCT_STORAGE_STANDARD_SERVER:
                        result += BUG_T(" Storage Standard Server Edition");
                        break;
                    case 0x00000016: // == PRODUCT_STORAGE_WORKGROUP_SERVER:
                        result += BUG_T(" Storage Workgroup Server Edition");
                        break;
                    case 0x00000017: // == PRODUCT_STORAGE_ENTERPRISE_SERVER:
                        result += BUG_T(" Storage Enterprise Server Edition");
                        break;
                    case 0x00000018: // == PRODUCT_SERVER_FOR_SMALLBUSINESS:
                        result += BUG_T(" Server Edition for Small Business");
                        break;
                    case 0x00000023: // == PRODUCT_SERVER_FOR_SMALLBUSINESS_V:
                        result += BUG_T(" Server Edition without Hyper-V for Small Business");
                        break;
                    case 0x00000019: // == PRODUCT_SMALLBUSINESS_SERVER_PREMIUM:
                        result += BUG_T(" Small Business Server Premium Edition");
                        break;
                    case 0xABCDABCD: // == PRODUCT_UNLICENSED:
                        result += BUG_T(" Unlicensed");
                        break;
                    }
                    if (9 == si.wProcessorArchitecture) // 9 == PROCESSOR_ARCHITECTURE_AMD64
                    {
                        result += BUG_T(", 64-bit");
                    }
                    else
                    if (0 == si.wProcessorArchitecture) // 0 == PROCESSOR_ARCHITECTURE_INTEL
                    {
                        result += BUG_T(", 32-bit");
                    }
                }
                return result;
                
            case 5:
                switch(osvi.dwMinorVersion)
                {
                case 2:
                    if (GetSystemMetrics(89)) // 89 == SM_SERVERR2
                    {
                        result = BUG_T("Microsoft Windows Server 2003 \"R2\"");
                    }
                    else
                    if (VER_NT_WORKSTATION == osvi.wProductType  && 9 == si.wProcessorArchitecture) // 9 == PROCESSOR_ARCHITECTURE_AMD64
                    {
                        result = BUG_T("Microsoft Windows XP Professional x64 Edition");
                    }
                    else
                    {
                        result = BUG_T("Microsoft Windows Server 2003,");
                    }
                    break;
                    
                case 1:
                    result = BUG_T("Microsoft Windows XP");
                    break;
                
                case 0:
                    result = BUG_T("Microsoft Windows 2000");
                    break;
                
                }
                break;
            
            case 4:
            case 3:
            case 2:
            case 1:
                result = BUG_T("Microsoft Windows NT");
                break;
                
            }

            // Test for specific product on Windows NT 4.0 SP6 and later.
            if (sizeof(osvi) == osvi.dwOSVersionInfoSize)
            {
                // Test for the workstation type.
                if (VER_NT_WORKSTATION == osvi.wProductType && 9 != si.wProcessorArchitecture) // 9 == PROCESSOR_ARCHITECTURE_AMD64
                {
                    if (4 == osvi.dwMajorVersion)
                    {
                        result += BUG_T(" Workstation 4.0");
                    }
                    else
                    if (osvi.wSuiteMask & 0x00000200) // 0x00000200 == VER_SUITE_PERSONAL
                    {
                        result += BUG_T(" Home Edition");
                    }
                    else
                    {
                        result += BUG_T(" Professional");
                    }
                }

                // Test for the server type.
                else
                if (VER_NT_SERVER == osvi.wProductType || VER_NT_DOMAIN_CONTROLLER == osvi.wProductType)
                {
                    if (5 == osvi.dwMajorVersion && 2 == osvi.dwMinorVersion)
                    {
                        if (PROCESSOR_ARCHITECTURE_IA64 == si.wProcessorArchitecture)
                        {
                            if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
                            {
                                result += BUG_T(" Datacenter Edition for Itanium-based Systems");
                            }
                            else
                            if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
                            {
                                result += BUG_T(" Enterprise Edition for Itanium-based Systems");
                            }
                        }
                        else
                        if (9 == si.wProcessorArchitecture) // 9 == PROCESSOR_ARCHITECTURE_AMD64
                        {
                            if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
                            {
                                result += BUG_T(" Datacenter x64 Edition");
                            }
                            else
                            if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
                            {
                                result += BUG_T(" Enterprise x64 Edition");
                            }
                            else
                            {
                                result += BUG_T(" Standard x64 Edition");
                            }
                        }
                        else
                        {
                            if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
                            {
                                result += BUG_T(" Datacenter Edition");
                            }
                            else
                            if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
                            {
                                result += BUG_T(" Enterprise Edition");
                            }
                            else
                            if (osvi.wSuiteMask & 0x00000400) // 0x00000400 == VER_SUITE_BLADE
                            {
                                result += BUG_T(" Web Edition");
                            }
                            else
                            {
                                result += BUG_T(" Standard Edition");
                            }
                        }
                    }
                    else
                    if (5 == osvi.dwMajorVersion && 0 == osvi.dwMinorVersion)
                    {
                        if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
                        {
                            result += BUG_T(" Datacenter Server");
                        }
                        else
                        if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
                        {
                            result += BUG_T(" Advanced Server");
                        }
                        else
                        {
                            result += BUG_T(" Server");
                        }
                    }
                    else  // Windows NT 4.0 
                    {
                        if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
                        {
                            result += BUG_T(" Server 4.0, Enterprise Edition");
                        }
                        else
                        {
                            result += BUG_T(" Server 4.0");
                        }
                    }
                }
            }
            else  
            {
                // Test for specific product on Windows NT 4.0 SP5 and earlier
                
                HKEY hKey;
                char szProductType[80];
                DWORD dwBufLen= sizeof(szProductType);
                LONG lRet;

                lRet = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\ProductOptions", 0, KEY_QUERY_VALUE, &hKey);
                if (lRet != ERROR_SUCCESS)
                {
                    return result;
                }
                lRet = RegQueryValueExA(hKey, "ProductType", NULL, NULL, (LPBYTE)szProductType, &dwBufLen);
                RegCloseKey(hKey);
                if ((lRet != ERROR_SUCCESS) || (sizeof(szProductType) < dwBufLen))
                {
                    return result;
                }

                if (0 == lstrcmpiA("WINNT", szProductType))
                {
                    result += BUG_T(" Workstation");
                }
                if (0 == lstrcmpiA("LANMANNT", szProductType))
                {
                    result += BUG_T(" Server");
                }
                if (0 == lstrcmpiA("SERVERNT", szProductType))
                {
                    result += BUG_T(" Advanced Server");
                }
                result += bug_form(BUG_T(" %d.%d"), osvi.dwMajorVersion, osvi.dwMinorVersion);
            }

            // Display service pack (if any) and build number.

            if (4 == osvi.dwMajorVersion && 0 == lstrcmpi(osvi.szCSDVersion, TEXT("Service Pack 6")))
            { 
                HKEY hKey;
                LONG lRet;

                // Test for SP6 versus SP6a.
                lRet = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Hotfix\\Q246009", 0, KEY_QUERY_VALUE, &hKey);
                if (lRet == ERROR_SUCCESS)
                {
                    result += bug_form(BUG_T(" Service Pack 6a (Build %d)"), osvi.dwBuildNumber & 0xFFFF);
                }
                else // Windows NT 4.0 prior to SP6a
                {
                    if (osvi.szCSDVersion[0])
                    {
                        result += BUG_T(' ');
                        result += osvi.szCSDVersion;
                    }
                    result += bug_form(BUG_T(" (Build %d)"), osvi.dwBuildNumber & 0xFFFF);
                }
                RegCloseKey(hKey);
            }
            else // not Windows NT 4.0 
            {
                if (osvi.szCSDVersion[0])
                {
                    result += BUG_T(' ');
                    result += osvi.szCSDVersion;
                }
                result += bug_form(BUG_T(" (Build %d)"), osvi.dwBuildNumber & 0xFFFF);
            }

        break;

        // Test for the Windows Me/98/95.
        case VER_PLATFORM_WIN32_WINDOWS:
            if (4 == osvi.dwMajorVersion)
            {
                switch(osvi.dwMinorVersion)
                {
                case 0:
                    result = BUG_T("Microsoft Windows 95");
                    if (BUG_T('C') == osvi.szCSDVersion[1] || BUG_T('B') == osvi.szCSDVersion[1])
                    {
                        result += BUG_T(" OSR2");
                    }
                    break;
                    
                case 10:
                    result = BUG_T("Microsoft Windows 98");
                    if (BUG_T('A') == osvi.szCSDVersion[1] || BUG_T('B') == osvi.szCSDVersion[1])
                    {
                        result += BUG_T(" SE");
                    }
                    break;
                    
                case 90:
                    result = BUG_T("Microsoft Windows Millennium Edition");
                    break;
                    
                }
            }
            break;

        case VER_PLATFORM_WIN32s:
            result = BUG_T("Microsoft Win32s");
            break;
            
        }
        
        return result;
    }
#endif
#endif
    
    
    ///////////////////////////////////////////////////////////////////////////////
    //
    //  mutex/lock
    //

#if defined(BUG_SINGLE_THREAD)
    class bug_mutex
    {
    public:
        void lock() { }
        void unlock() { }
    };
#elif defined(BUG_MS_WINDOWS)
    class bug_mutex
    {
        HANDLE mutex;
    public:
        bug_mutex()
            :mutex(CreateMutex(NULL, FALSE, NULL))
        {
        }
        ~bug_mutex()
        {
            CloseHandle(mutex);
        }
        void lock()
        {
            WaitForSingleObject(mutex, INFINITE);
        }
        void unlock()
        {
            ReleaseMutex(mutex);
        }
    };
#else
    class bug_mutex
    {
        pthread_mutex_t mutex;
    public:
        bug_mutex()
        {
            pthread_mutex_init(&mutex, NULL);
        }
        ~bug_mutex()
        {
            pthread_mutex_destroy(&mutex);
        }
        void lock()
        {
            pthread_mutex_lock(&mutex);
        }
        void unlock()
        {
            pthread_mutex_unlock(&mutex);
        }
    };
#endif
#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable:4512)
#endif
    class bug_lock
    {
        bug_mutex & mutex;
    public:
        bug_lock(bug_mutex & a_mutex) :mutex(a_mutex)
        {
            mutex.lock();
        }
        ~bug_lock()
        {
            mutex.unlock();
        }
    };
    class bug_unlock
    {
        bug_mutex & mutex;
    public:
        bug_unlock(bug_mutex & a_mutex) :mutex(a_mutex)
        {
            mutex.unlock();
        }
        ~bug_unlock()
        {
            mutex.lock();
        }
    };
#if defined(_MSC_VER)
#   pragma warning(pop)
#endif

    
    ///////////////////////////////////////////////////////////////////////////////
    //
    //  smart pointer
    //

    //
    //  bug_smart_ptr_ref_cnt
    //

    //  スマートポインタを介して使用することが前提となるクラスは予めこのクラス
    //  継承しておくことで bug_smart_ptr_share<T> を使用しないで済む分、効率的
    //  になります。
    
    class bug_smart_ptr_ref_cnt
    {
    private:
        int ref_count;
        bug_mutex mutex;
        
    public:
        bug_smart_ptr_ref_cnt() :ref_count(0) { }
        bug_smart_ptr_ref_cnt(const bug_smart_ptr_ref_cnt &) :ref_count(0) { }
        virtual ~bug_smart_ptr_ref_cnt() { }
        
        void ref_inc()
        {
            assert(0 <= ref_count);
            bug_lock(this->mutex), ++ref_count;
            assert(0 < ref_count);
        }
        
        void ref_dec()
        {
            assert(0 < ref_count);
            bug_lock(this->mutex), --ref_count;
            assert(0 <= ref_count);
            if (ref_count <= 0)
            {
                delete this;
            }
        }
    };

    //
    //  bug_smart_ptr_share
    //

    template<class target_T>
    class bug_smart_ptr_share :public bug_smart_ptr_ref_cnt
    {
    private:
        bug_smart_ptr_share(const bug_smart_ptr_share &); // コピー禁止
        
    public:
        target_T * target;
        
        bug_smart_ptr_share(target_T * a_target) :target(a_target) { }
        ~bug_smart_ptr_share()
        {
            delete target;
        }
        
        operator target_T * ()
        {
            return target;
        }
        operator const target_T * () const
        {
            return target;
        }
    };

    //
    //  utility for bug_smart_ptr　
    //

    template<class target_T>
    inline bug_smart_ptr_ref_cnt * get_bug_smart_by_target(target_T *, bug_smart_ptr_ref_cnt * smart)
    {
        return smart;
    }
    template<class target_T>
    inline bug_smart_ptr_ref_cnt * get_bug_smart_by_target(target_T * target, ...)
    {
        return new bug_smart_ptr_share<target_T>(target);
    }
    template<class target_T>
    inline target_T * get_target_by_bug_smart(bug_smart_ptr_ref_cnt * smart, target_T *, bug_smart_ptr_ref_cnt *)
    {
        return (target_T *)smart;
    }
    template<class target_T>
    inline target_T * get_target_by_bug_smart(bug_smart_ptr_ref_cnt * smart, target_T *, ...)
    {
        return *(bug_smart_ptr_share<target_T> *)(smart);
    }
    
    //
    //  bug_smart_ptr
    //

    //  リファレンスカウンタ(bug_smart_ptr_ref_cnt)の内包型と外付型をシームレス
    //  に扱えるスマートポインタです。
    
#if defined(__WATCOMC__)
#define bug_smart_ptr_target_T
#else
#define bug_smart_ptr_target_T  <target_T>
#endif

    template<class target_T>
    class bug_smart_ptr
    {
    protected:
        bug_smart_ptr_ref_cnt * target;
        target_T * get_target()
        {
            return get_target_by_bug_smart bug_smart_ptr_target_T (target, (target_T *)NULL, (target_T *)NULL);
        }
        const target_T * get_target() const
        {
            return get_target_by_bug_smart bug_smart_ptr_target_T (target, (target_T *)NULL, (target_T *)NULL);
        }
        
    public:
        bug_smart_ptr(target_T * a_target = NULL) :target(get_bug_smart_by_target bug_smart_ptr_target_T (a_target, a_target))
        {
            if (target)
            {
                target->bug_smart_ptr_ref_cnt::ref_inc();
            }
        }
        bug_smart_ptr(const bug_smart_ptr<target_T> & a) :target(a.target)
        {
            if (target)
            {
                target->bug_smart_ptr_ref_cnt::ref_inc();
            }
        }
        ~bug_smart_ptr()
        {
            release();
        }
        
        operator target_T * ()
        {
            return get_target();
        }
        operator const target_T * () const
        {
            return get_target();
        }
        target_T * operator -> ()
        {
            return get_target();
        }
        const target_T * operator -> () const
        {
            return get_target();
        }
        target_T & operator * ()
        {
            return *get_target();
        }
        const target_T & operator * () const
        {
            return *get_target();
        }
        
        bug_smart_ptr<target_T> & operator = (target_T * a_target)
        {
            release();
            set(get_bug_smart_by_target bug_smart_ptr_target_T (a_target, a_target));
            return *this;
        }
        bug_smart_ptr<target_T> & operator = (const bug_smart_ptr<target_T> & a)
        {
            release();
            set(a.target);
            return *this;
        }
        
        void release()
        {
            if (target)
            {
                target->bug_smart_ptr_ref_cnt::ref_dec();
                target = NULL;
            }
        }
        
        bool is_null() const
        {
            return !target;
        }
        operator bool () const
        {
            return target;
        }
        bool operator ! () const
        {
            return is_null();
        }
    protected:
        void set(bug_smart_ptr_ref_cnt * a_target)
        {
            target = a_target;
            if (target)
            {
                target->bug_smart_ptr_ref_cnt::ref_inc();
            }
        }
    };


    ///////////////////////////////////////////////////////////////////////////
    //
    //  bug_thread_local_storage
    //

#if defined(BUG_THREAD_LOCAL_STORAGE)
    template<class target_T> class bug_thread_local_storage_base
    {
    private:
        static BUG_THREAD_LOCAL_STORAGE(target_T *) tls_ptr;
    protected:
        static void init()
        {
        }
        static target_T * get_target_storage()
        {
            return tls_ptr;
        }
        static void set_target_storage(target_T * target)
        {
            tls_ptr = target;
        }
    };
    template<class target_T> BUG_THREAD_LOCAL_STORAGE(target_T *) bug_thread_local_storage_base<target_T>::tls_ptr = NULL;
#elif defined(BUG_MS_WINDOWS)
    template<class target_T> class bug_thread_local_storage_base
    {
    private:
        static volatile DWORD tls_handle;
    protected:
        static void init()
        {
            if (TLS_OUT_OF_INDEXES == tls_handle)
            {
                const bug_char mutex_name[] = BUG_T("TrickLibrary::TLS::Init"); // 直接文字列リテラルを CreateMutex の引数に使用すると ERROR_NOACCESS になる場合があるのでスタックを経由する。
                HANDLE mutex_handle = BUG_API_T(CreateMutex)(NULL, TRUE, mutex_name);
                assert(NULL != mutex_handle);
                WaitForSingleObject(mutex_handle, INFINITE);
                if (TLS_OUT_OF_INDEXES == tls_handle)
                {
                    tls_handle = TlsAlloc();
                    assert(NULL != mutex_handle);
                }
                CloseHandle(mutex_handle);
                assert(TLS_OUT_OF_INDEXES != tls_handle);
            }
        }
        static target_T * get_target_storage()
        {
            if (TLS_OUT_OF_INDEXES == tls_handle)
            {
                return (target_T *)NULL;
            }
            else
            {
                return (target_T *)TlsGetValue(tls_handle);
            }
        }
        static void set_target_storage(target_T * target)
        {
            assert(TLS_OUT_OF_INDEXES != tls_handle);
            if (TLS_OUT_OF_INDEXES != tls_handle)
            {
                TlsSetValue(tls_handle, target);
            }
        }
    };
    template<class target_T> volatile DWORD bug_thread_local_storage_base<target_T>::tls_handle = TLS_OUT_OF_INDEXES;
#else
    template<class target_T> class bug_thread_local_storage_base
    {
        static pthread_key_t tls_handle;
        static pthread_once_t tls_handle_init_once;

        static void tls_handle_destroy(void * tls_handle)
        {
            //  実際にはここに到達される前に削除されていなければならない。
            assert(NULL == tls_handle);
            delete (target_T *)tls_handle;
        }
        static void tls_handle_alloc()
        {
            pthread_key_create(&tls_handle, tls_handle_destroy);
        }

    public:
        static void init()
        {
            pthread_once(&tls_handle_init_once, tls_handle_alloc);
        }
        static target_T * get_target_storage()
        {
            if (0 == tls_handle) // 0 で問題なさげだが、保証はなし。
            {
                return (target_T *)NULL;
            }
            else
            {
                return (target_T *)pthread_getspecific(tls_handle);
            }
        }
        static void set_target_storage(target_T * target)
        {
            pthread_setspecific(tls_handle, target);
        }
    };
    template<class target_T> pthread_key_t bug_thread_local_storage_base<target_T>::tls_handle = 0; // 0 で問題なさげだが、保証はなし。
    template<class target_T> pthread_once_t bug_thread_local_storage_base<target_T>::tls_handle_init_once = PTHREAD_ONCE_INIT;
#endif
    template<class target_T> class bug_thread_local_storage
        :public bug_thread_local_storage_base<target_T>
    {
        typedef bug_thread_local_storage_base<target_T> base_type;
    public:
        bug_thread_local_storage(target_T * new_target)
        {
            init(new_target);
        }
        ~bug_thread_local_storage()
        {
            uninit();
        }
        static void init(target_T * new_target)
        {
            base_type::init();
            base_type::set_target_storage(new_target);
        }
        static void uninit()
        {
            target_T * target = base_type::get_target_storage();
            if (target)
            {
                delete target;
                base_type::set_target_storage(NULL);
            }
        }
        static target_T * get_target()
        {
            return base_type::get_target_storage();
        }
    };
    
    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  bug_writer
    //

    class bug_writer
    {
    public:
        virtual ~bug_writer() { }
        virtual void write(const bug_string & message) = 0;
    };

        class bug_smart_writer :private bug_writer, public bug_smart_ptr<bug_writer>
        {
        public:
            bug_smart_writer(bug_writer * a) :bug_smart_ptr<bug_writer>(a) { }
            bug_smart_writer(const bug_smart_writer & a) :bug_smart_ptr<bug_writer>(a) { }
            void write(const bug_string & message)
            {
                (**this).write(message);
            }
            operator bug_writer * () const
            {
                return reinterpret_cast<bug_writer *>(new bug_smart_writer(*this));
            }
        };
        
        class bug_file_writer_base :public bug_writer
        {
        protected:
            FILE * handle;
        public:
            bug_file_writer_base(FILE * a_handle = stderr) :handle(a_handle) { }
            void write(const bug_string & message)
            {
                if (handle)
                {
                    fwrite(message.data(), sizeof(bug_string::value_type), message.size(), handle);
                    fflush(handle);
                }
            };
        };
#if !defined(BUG_MS_WINDOWS)
            class bug_file_writer :public bug_file_writer_base
            {
            public:
                bug_file_writer(const std::basic_string<char> & filename)
                    :bug_file_writer_base(fopen(filename.c_str(), "a")) { }
                ~bug_file_writer()
                {
                    if (handle)
                    {
                        fclose(handle);
                    }
                }
            };
#endif
        
#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable:4512)
#endif
        class bug_stream_writer :public bug_writer
        {
        protected:
            std::ostream & stream;
        public:
            bug_stream_writer(std::ostream & a_stream = std::cerr) :stream(a_stream) { }
            void write(const bug_string & message)
            {
                if (stream)
                {
                    stream.write((const char *)message.data(), message.size() *sizeof(bug_string::value_type));
                    stream.flush();
                }
            };
        };
#if defined(_MSC_VER)
#   pragma warning(pop)
#endif

            class bug_fstream_writer :public bug_stream_writer
            {
            protected:
                std::ofstream file;
            public:
            
#if defined(_MSC_VER) && 1300 <= _MSC_VER
                bug_fstream_writer(const bug_string & filename)
#else
                bug_fstream_writer(const std::basic_string<char> & filename)
#endif
                    :bug_stream_writer(file), file(filename.c_str(), std::ios::app) { }
            };

#if defined(BUG_MS_WINDOWS)

#if !defined(FILE_WRITE_TO_END_OF_FILE)
#define FILE_WRITE_TO_END_OF_FILE       0xFFFFFFFF
#endif

        class bug_handle_writer :public bug_writer
        {
        protected:
            HANDLE handle;
        public:
            bug_handle_writer(HANDLE a_handle = GetStdHandle(STD_ERROR_HANDLE)) :handle(a_handle) { }
            void write(const bug_string & message)
            {
                if (INVALID_HANDLE_VALUE != handle)
                {
                    DWORD written_size = 0;
                    OVERLAPPED ol;
                    memset(&ol, 0, sizeof(ol));
                    ol.Offset = FILE_WRITE_TO_END_OF_FILE;
                    ol.OffsetHigh = (DWORD)-1;
                    WriteFile(handle, message.data(), (DWORD)(message.size() *sizeof(bug_string::value_type)), &written_size, &ol);
                    //FlushFileBuffers(handle);
                    //↑その都度フラッシュをやってると環境によってはフラッシュを
                    //その都度やらない場合に比べて動作が数十倍も重くなる。
                    //どうもフラッシュが必要なのは電源断などの物理障害に対してで
                    //あってアプリが異常終了した程度であればフラッシュをやってな
                    //くても問題なさげ(根拠なし)。
                    // cf. http://support.microsoft.com/kb/332023/ja
                }
            };
        };
            class bug_file_writer :public bug_handle_writer
            {
            public:
                bug_file_writer(const std::basic_string<char> & filename)
                    :bug_handle_writer
                    (
                        CreateFileA
                        (
                            filename.c_str(), GENERIC_WRITE, FILE_SHARE_READ |FILE_SHARE_WRITE,
                            NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
                        )
                    )
                {
                }
                bug_file_writer(const std::basic_string<wchar_t> & filename)
                    :bug_handle_writer
                    (
                        CreateFileW
                        (
                            filename.c_str(), GENERIC_WRITE, FILE_SHARE_READ |FILE_SHARE_WRITE,
                            NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
                        )
                    )
                {
                }
                ~bug_file_writer()
                {
                    if (INVALID_HANDLE_VALUE != handle)
                    {
                        CloseHandle(handle);
                    }
                }
            };
        class bug_OutputDebugString_writer :public bug_writer
        {
        public:
            void write(const std::basic_string<char> & message)
            {
                OutputDebugStringA(message.c_str());
            };
            void write(const std::basic_string<wchar_t> & message)
            {
                OutputDebugStringW(message.c_str());
            };
        };
#endif


    ///////////////////////////////////////////////////////////////////////////
    //
    //  bug_stamp
    //

    class bug_stamp
    {
    public:
        virtual ~bug_stamp() { }
        virtual const bug_string get_stamp() = 0;
    };

        class bug_smart_stamp :private bug_stamp, public bug_smart_ptr<bug_stamp>
        {
        public:
            bug_smart_stamp(bug_stamp * a) :bug_smart_ptr<bug_stamp>(a) { }
            bug_smart_stamp(const bug_smart_stamp & a) :bug_smart_ptr<bug_stamp>(a) { }
            const bug_string get_stamp()
            {
                return (**this).get_stamp();
            }
            operator bug_stamp * () const
            {
                return reinterpret_cast<bug_stamp *>(new bug_smart_stamp(*this));
            }
        };
        
        class bug_counter_stamp :public bug_stamp
        {
        protected:
            unsigned int counter;
        public:
            bug_counter_stamp() :counter(0) { }
            const bug_string get_stamp()
            {
                return bug_form(BUG_T("%d"), counter++);
            };
        };
            class bug_hex_counter_stamp :public bug_counter_stamp
            {
            public:
                const bug_string get_stamp()
                {
                    return bug_form(BUG_T("0x%08.8X"), counter++);
                };
            };
            //  マルチスレッド環境下で、この bug_counter_stamp と bug_hex_counter_stamp
            //  は正常に動作することが期待できないが、普通に使う分にはクリティカルな
            //  問題ではないので、当面は対処しない。get_stamp() の値が一意であることを
            //  期待するなら同期オブジェクトを用いカウンタのインクリメント時にロックを
            //  行うこと。
            
        class bug_clock_stamp :public bug_stamp
        {
        private:
            time_t init_start_day_time()
            {
                bug_clock now;
                return now.total_sec -((((now.hour *60) +now.min) *60) +now.sec);
            }
        protected:
            int get_hour(const bug_clock & clock)
            {
                static time_t start_day_time = init_start_day_time();
                return ((clock.total_sec -start_day_time) /(60 *60)) %100;
            }
        public:
            const bug_string get_stamp()
            {
                bug_clock now;
                return bug_form(BUG_T("%2.2d:%2.2d:%2.2d"), get_hour(now), now.min, now.sec);
            }
        };
            class bug_clock_stamp_with_date :public bug_clock_stamp
            {
            public:
                const bug_string get_stamp()
                {
                    bug_clock now;
                    return bug_term::stamp_title +bug_form(BUG_T("%4.4d-%2.2d-%2.2d(%s) %2.2d:%2.2d:%2.2d"), now.year, now.mon, now.mday, bug_term::wday_names[now.wday], now.hour, now.min, now.sec);
                }
            };

            //  コンパクト表示( bug_stamp としてももちろん使用できるが、主目的はファイル名生成用 )
            class bug_short_clock_stamp :public bug_clock_stamp
            {
            public:
                const bug_string get_stamp()
                {
                    bug_clock now;
                    return bug_form(BUG_T("%2.2d%2.2d%2.2d"), get_hour(now), now.min, now.sec);
                }
            };
            class bug_short_clock_stamp_with_date :public bug_clock_stamp
            {
            public:
                const bug_string get_stamp()
                {
                    bug_clock now;
                    return bug_form(BUG_T("%4.4d%2.2d%2.2d.%2.2d%2.2d%2.2d"), now.year, now.mon, now.mday, now.hour, now.min, now.sec);
                }
            };

#if !defined(__MWERKS__)
            //  ミリ秒付き表示
            class bug_clock_stamp_ex :public bug_clock_stamp
            {
            public:
                const bug_string get_stamp()
                {
                    bug_clock now;
                    return bug_form(BUG_T("%2.2d:%2.2d:%2.2d.%3.3d"), get_hour(now), now.min, now.sec, now.milli);
                }
            };
            class bug_clock_stamp_ex_with_date :public bug_clock_stamp
            {
            public:
                const bug_string get_stamp()
                {
                    bug_clock now;
                    return bug_term::stamp_title +bug_form(BUG_T("%4.4d-%2.2d-%2.2d(%s) %2.2d:%2.2d:%2.2d.%3.3d"), now.year, now.mon, now.mday, bug_term::wday_names[now.wday], now.hour, now.min, now.sec, now.milli);
                }
            };
#if !defined(BUG_MS_WINDOWS)
            //  マイクロ秒付き表示
            class bug_clock_stamp_ex2 :public bug_clock_stamp
            {
            public:
                const bug_string get_stamp()
                {
                    bug_clock now;
                    return bug_form(BUG_T("%2.2d:%2.2d:%2.2d.%6.6d"), get_hour(now), now.min, now.sec, now.usec);
                }
            };
            class bug_clock_stamp_ex2_with_date :public bug_clock_stamp
            {
            public:
                const bug_string get_stamp()
                {
                    bug_clock now;
                    return bug_term::stamp_title +bug_form(BUG_T("%4.4d-%2.2d-%2.2d(%s) %2.2d:%2.2d:%2.2d.%6.6d"), now.year, now.mon, now.mday, bug_term::wday_names[now.wday], now.hour, now.min, now.sec, now.usec);
                }
            };
#endif
#endif

#if defined(BUG_MS_WINDOWS)
        class bug_GetTickCount_stamp :public bug_stamp
        {
        public:
            const bug_string get_stamp()
            {
                return bug_form(BUG_T("%08.8X"), GetTickCount());
            };
        };
        class bug_QueryPerformanceFrequency
        {
        public:
            LARGE_INTEGER value;
            
            bug_QueryPerformanceFrequency()
            {
                QueryPerformanceFrequency(&value);
            }
        };
        class bug_QueryPerformanceCounter_stamp :public bug_stamp
        {
        public:
            const bug_string get_stamp()
            {
                LARGE_INTEGER performance_counter;
                QueryPerformanceCounter(&performance_counter);
                return bug_form(BUG_T("%08.8X%08.8X"), performance_counter.HighPart, performance_counter.LowPart);
            };
        };
        class bug_QueryPerformanceSecond_stamp :public bug_stamp
        {
        public:
            const bug_string get_stamp()
            {
                static bug_QueryPerformanceFrequency frequency; // 本当は排他をかけた初期化を行うべき。
                LARGE_INTEGER performance_counter;
                QueryPerformanceCounter(&performance_counter);
                int sec = static_cast<int>(performance_counter.QuadPart /frequency.value.QuadPart);
                LONGLONG usec64 = (performance_counter.QuadPart %frequency.value.QuadPart) *1000000 /frequency.value.QuadPart;
                int usec = static_cast<int>(usec64);
                
                return bug_form(BUG_T("%7d.%06.6d"), sec, usec);
            };
        };
#endif

#if defined(__MWERKS__)
    typedef bug_clock_stamp bug_default_stamp;
#else
    typedef bug_clock_stamp_ex bug_default_stamp;
#endif
    

    ///////////////////////////////////////////////////////////////////////////
    //
    //  bug_message
    //

    class bug_message
    {
#if !defined(BUG_WITHOUT_LOCATION_INFO)
        const bug_char * file;
        unsigned int line;
#if defined(BUG_FUNCTION_NAME)
        const bug_char * function_name;
#endif
#endif
        bug_string message;
    public:
        typedef bug_message this_type;

#if defined(BUG_WITHOUT_LOCATION_INFO)
        bug_message(const bug_char * a_message = BUG_T(""))
            :message(a_message) { }
        bug_message(const bug_string & a_message)
            :message(a_message) { }
        bug_message(const this_type & a)
            :message(a.message) { }
        bug_message(const this_type & a, const bug_string & a_message)
            :message(a_message) { }
#elif defined(BUG_FUNCTION_NAME)
        bug_message(const bug_char * a_message = BUG_T(""))
            :file(0), line(0), function_name(0), message(a_message) { }
        bug_message(const bug_string & a_message)
            :file(0), line(0), function_name(0), message(a_message) { }
        bug_message(const bug_char * a_file, unsigned int a_line, const bug_char * a_function_name, const bug_string & a_message = BUG_T(""))
            :file(a_file), line(a_line), function_name(a_function_name), message(a_message) { }
        bug_message(const this_type & a)
            :file(a.file), line(a.line), function_name(a.function_name), message(a.message) { }
        bug_message(const this_type & a, const bug_string & a_message)
            :file(a.file), line(a.line), function_name(a.function_name), message(a_message) { }
#else
        bug_message(const bug_char * a_message = BUG_T(""))
            :file(0), line(0), message(a_message) { }
        bug_message(const bug_string & a_message)
            :file(0), line(0), message(a_message) { }
        bug_message(const bug_char * a_file, unsigned int a_line, const bug_string & a_message = BUG_T(""))
            :file(a_file), line(a_line), message(a_message) { }
        bug_message(const this_type & a)
            :file(a.file), line(a.line), message(a.message) { }
        bug_message(const this_type & a, const bug_string & a_message)
            :file(a.file), line(a.line), message(a_message) { }
#endif
            
#if !defined(BUG_WITHOUT_LOCATION_INFO)
        const bug_string get_file() const
        {
            if (file)
            {
                return file;
            }
            else
            {
                return bug_term::unknown_location;
            }
        }
        unsigned int get_line() const { return line; }
#if defined(BUG_FUNCTION_NAME)
        const bug_string get_function_name() const
        {
            if (function_name)
            {
                return function_name;
            }
            else
            {
                return bug_term::unknown_function;
            }
        }
#endif
#endif
        const bug_string & get_message() const
        {
            return message;
        }
#if !defined(BUG_WITHOUT_LOCATION_INFO)
        const bug_string get_location() const
        {
            if (file)
            {
#if defined(BUG_FUNCTION_NAME)
                return bug_form(bug_term::location_format, file, line, get_function_name().c_str());
#else
                return bug_form(bug_term::location_format, file, line);
#endif
            }
            else
            {
                return bug_term::unknown_location;
            }
        }
#endif

        const bug_string get_message_ex() const
        {
#if defined(BUG_WITHOUT_LOCATION_INFO)
            return message;
#else
            if (BUG_T("") == message)
            {
                return get_location();
            }
            else
            {
                return message;
            }
#endif
        }

        const bug_string get_full_message() const
        {
#if defined(BUG_WITHOUT_LOCATION_INFO)
            return message;
#else
            if (0 == file)
            {
                return message;
            }
            else
            if (BUG_T("") == message)
            {
                return get_location();
            }
            else
            {
                return message +BUG_T(" ") +get_location();
            }
#endif
        }

        this_type create(const bug_string & a_message) const
        {
            return this_type(*this, a_message);
        }
		static const bug_message get_overall()
		{
			return this_type
			(
#if !defined(BUG_WITHOUT_LOCATION_INFO)
				bug_term::overall_scope_label, 0,
#if defined(BUG_FUNCTION_NAME)
				bug_term::overall_scope_label,
#endif
#endif
				bug_term::overall_scope_label
			);
		}

        this_type & operator = (const this_type & a)
        {
#if !defined(BUG_WITHOUT_LOCATION_INFO)
            file = a.file;
            line = a.line;
#if defined(BUG_FUNCTION_NAME)
            function_name = a.function_name;
#endif
#endif
            message = a.message;
            return *this;
        }
        
        friend bool operator == (const bug_message & a, const bug_message & b)
        {
            return
#if !defined(BUG_WITHOUT_LOCATION_INFO)
                a.file == b.file &&
                a.line == b.line &&
#if defined(BUG_FUNCTION_NAME)
                a.function_name == b.function_name &&
#endif
#endif
                a.message == b.message;
        }
        friend bool operator < (const bug_message & a, const bug_message & b)
        {
            return
#if !defined(BUG_WITHOUT_LOCATION_INFO)
                a.file < b.file ||
                (
                    a.file == b.file &&
                    (
                        a.line < b.line ||
                        (
                            a.line == b.line &&
                            (
#if defined(BUG_FUNCTION_NAME)
                                a.function_name < b.function_name ||
                                (
                                    a.function_name == b.function_name &&
                                    (
#endif
#endif
                                        a.message < b.message
#if !defined(BUG_WITHOUT_LOCATION_INFO)
#if defined(BUG_FUNCTION_NAME)
                                    )
                                )
#endif
                            )
                        )
                    )
                )
#endif
                ;
        }
    };

    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  bug_get_process_id(), bug_get_thread_id()
    //

#if defined(BUG_MULTI_PROCESS)
    int bug_get_process_id()
    {
#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable:4996)
#endif
        return getpid();
#if defined(_MSC_VER)
#   pragma warning(pop)
#endif
    }
#endif
#if defined(BUG_MULTI_THREAD)
    int bug_get_thread_id()
    {
#if defined(BUG_MS_WINDOWS)
        return GetCurrentThreadId();
#else
        return (int)pthread_self();
#endif
    }
#endif

    ///////////////////////////////////////////////////////////////////////////
    //
    //  bug_dummy_if
    //

    class bug_dummy_if { };
    
    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  bug_logger
    //

    class bug_logger :public bug_dummy_if
    {
    private:
        bug_stamp * stamp;
        bug_string last_stamp;
    protected:
        bug_writer * writer;
        unsigned int level;
    public:
        typedef bug_logger this_type;

#if defined(_MSC_VER) && _MSC_VER <= 1200
        bug_logger()
            :writer(new bug_stream_writer()), stamp(new bug_default_stamp()), level(0) { }
        bug_logger(bug_writer * a_writer)
            :writer(a_writer), stamp(new bug_default_stamp()), level(0) { }
        bug_logger(bug_writer * a_writer, bug_stamp * a_stamp)
#else
        bug_logger(bug_writer * a_writer = new bug_stream_writer(), bug_stamp * a_stamp = new bug_default_stamp())
#endif
            :writer(a_writer), stamp(a_stamp), level(0) { }
        virtual ~bug_logger() { delete writer; delete stamp; }

        const bug_string & get_last_stamp() const
        {
            if (this)
            {
                return last_stamp;
            }
            else
            {
                return bug_term::no_stamp_message;
            }
        }
        const bug_string & get_new_stamp()
        {
            if (this)
            {
                return last_stamp = stamp->get_stamp();
            }
            else
            {
                return bug_term::no_stamp_message;
            }
        }
                    
        this_type & log_message(const bug_message & message)
        {
            if (this)
            {
                log_message_core(message);
            }
            return *this;
        }
        this_type & log_level_up(const bug_message & message)
        {
            if (this)
            {
                log_level_up_core(message);
                ++level;
            }
            return *this;
        }
        this_type & log_level_down(const bug_message & message)
        {
            if (this)
            {
                log_level_down_core(message);
                --level;
            }
            return *this;
        }
        virtual this_type & log_message_core(const bug_message & message) = 0;
        virtual this_type & log_level_up_core(const bug_message & message) = 0;
        virtual this_type & log_level_down_core(const bug_message & message) = 0;
        
        static this_type & get_instance()
        {
            return *(bugbeard::bug_thread_local_storage<this_type>::get_target());
        }
    };
    
        class bug_tsv_logger :public bug_logger
        {
        public:
            typedef bug_tsv_logger  this_type;
            typedef bug_logger      base_type;
#if defined(__MWERKS__)
            typedef bug_clock_stamp_with_date stamp_with_date_type;
#else
            typedef bug_clock_stamp_ex_with_date stamp_with_date_type;
#endif

            bug_tsv_logger(bug_writer * a_writer = new bug_stream_writer, bug_stamp * a_stamp = new bug_default_stamp)
                :bug_logger(a_writer, a_stamp)
            {
                top_sign();
            }
            ~bug_tsv_logger()
            {
                bottom_sign();
            }
            this_type & top_sign()
            {
#if !defined(BUG_WITHOUT_TSV_LOG_HEADER)
                output_header();
#endif // !defined(BUG_WITHOUT_TSV_LOG_HEADER)
                log_level_up(BUG_MSG(bug_term::begin_prefix +bug_term::session_root));
                log_message(BUG_MSG(stamp_with_date_type().get_stamp()));
                return *this;
            }
            this_type & bottom_sign()
            {
                log_message(BUG_MSG(stamp_with_date_type().get_stamp()));
                log_level_down(BUG_MSG(bug_term::end_prefix +bug_term::session_root));
                return *this;
            }
        private:
#if !defined(BUG_WITHOUT_TSV_LOG_HEADER)
            base_type & output_header()
            {
                const bug_string separetor = BUG_T("\t");
                writer->write
                (
                    bug_term::time_stamp_label +separetor +
#if defined(BUG_MULTI_PROCESS)
                    bug_term::process_id_labe +separetor +
#endif
#if defined(BUG_MULTI_THREAD)
                    bug_term::thread_id_label +separetor +
#endif
                    bug_term::level_label +separetor +
#if !defined(BUG_WITHOUT_LOCATION_INFO)
                    bug_term::file_label +separetor +
                    bug_term::line_label +separetor +
#if defined(BUG_FUNCTION_NAME)
                    bug_term::function_label +separetor +
#endif
#endif
                    bug_term::scope_label +bug_term::return_code
                );
                return *this;
            }
#endif // !defined(BUG_WITHOUT_TSV_LOG_HEADER)
            base_type & log_message_core(const bug_message & message)
            {
                writer->write
                (
                    get_new_stamp()
#if defined(BUG_MULTI_PROCESS) && defined(BUG_MULTI_THREAD)
                    +bug_form(BUG_T("\t%d\t%d\t%d\t"), bug_get_process_id(), bug_get_thread_id(), level)
#elif defined(BUG_MULTI_PROCESS)
                    +bug_form(BUG_T("\t%d\t%d\t"), bug_get_process_id(), level)
#elif defined(BUG_MULTI_THREAD)
                    +bug_form(BUG_T("\t%d\t%d\t"), bug_get_thread_id(), level)
#else
                    +bug_form(BUG_T("\t%d\t"), level)
#endif
#if !defined(BUG_WITHOUT_LOCATION_INFO)
                    +message.get_file()
                    +bug_form(BUG_T("\t%d\t"), message.get_line())
#if defined(BUG_FUNCTION_NAME)
                    +message.get_function_name()
                    +BUG_T("\t")
#endif
#endif
                    +message.get_message()
                    +bug_term::return_code
                );
                return *this;
            }
            base_type & log_level_up_core(const bug_message & message)
            {
                log_message(message);
                return *this;
            }
            base_type & log_level_down_core(const bug_message & message)
            {
                log_message(message);
                return *this;
            }
        };
        class bug_tree_logger :public bug_logger
        {
        public:
            typedef bug_tree_logger this_type;
            typedef bug_logger      base_type;
#if defined(__MWERKS__)
            typedef bug_clock_stamp_with_date stamp_with_date_type;
#else
            typedef bug_clock_stamp_ex_with_date stamp_with_date_type;
#endif

#if defined(BUG_MULTI_PROCESS) || defined(BUG_MULTI_THREAD)
            bug_string logger_id;
#endif
            bug_tree_logger(bug_writer * a_writer = new bug_stream_writer, bug_stamp * a_stamp = new bug_default_stamp)
                :bug_logger(a_writer, a_stamp)
#if defined(BUG_MULTI_PROCESS) && defined(BUG_MULTI_THREAD)
                ,logger_id(bug_form(BUG_T("%d\t%d\t"), bug_get_process_id(), bug_get_thread_id()))
#elif defined(BUG_MULTI_PROCESS)
                ,logger_id(bug_form(BUG_T("%d\t"), bug_get_process_id()))
#elif defined(BUG_MULTI_THREAD)
                ,logger_id(bug_form(BUG_T("%d\t"), bug_get_thread_id()))
#endif
            {
                top_sign();
            }
            ~bug_tree_logger() { bottom_sign(); }

            this_type & top_sign()
            {
                const bug_string long_stamp = stamp_with_date_type().get_stamp();
#if defined(BUG_LANG_JP)
                const int X = (int)((get_new_stamp().length() +1) /2 -1);
                if (BUG_T("") != long_stamp) {
                    log_message_line(BUG_T("┌") +bug_run_string(38, bug_term::horizon_line));
                    log_message_line(BUG_T("│") +long_stamp);

                    if (0 <= X) {
                        log_message_line(BUG_T("└") +bug_run_string(X, bug_term::horizon_line) +bug_run_string(level +1, BUG_T("┬")) +bug_run_string(38 -(X +level +1), bug_term::horizon_line));
                    } else {
                        log_message_line(BUG_T("├") +bug_run_string(38, bug_term::horizon_line));
                    }

                } else {

                    if (0 <= X) {
                        log_message_line(bug_run_string(X +1, bug_term::horizon_line) +bug_run_string(level +1, BUG_T("┬")) +bug_run_string(38 -(X +level +1), bug_term::horizon_line));
                    } else {
                        log_message_line(BUG_T("┬") +bug_run_string(38, bug_term::horizon_line));
                    }

                }
#endif  //  defined(BUG_LANG_JP)
#if defined(BUG_LANG_EN)
                log_message_line(bug_run_string(79, bug_term::horizon_line));
                log_message_line(BUG_T("\t") +long_stamp);
                log_message_line(bug_run_string(79, bug_term::horizon_line));
#endif  //  defined(BUG_LANG_EN)

                return *this;
            }
            this_type & bottom_sign()
            {
                const bug_string long_stamp = stamp_with_date_type().get_stamp();
#if defined(BUG_LANG_JP)
                const int X = (int)((get_new_stamp().length() +1) /2 -1);
                if (BUG_T("") != long_stamp)
                {
                    if (0 <= X)
                    {
                        log_message_line(BUG_T("┌") +bug_run_string(X, bug_term::horizon_line) +bug_run_string(level +1, BUG_T("┴")) +bug_run_string(38 -(X +level +1), bug_term::horizon_line));
                    }
                    else
                    {
                        log_message_line(BUG_T("├") +bug_run_string(38, bug_term::horizon_line));
                    }
                    log_message_line(BUG_T("│") +long_stamp);
                    log_message_line(BUG_T("└") +bug_run_string(38, bug_term::horizon_line));
                }
                else
                {
                    if (0 <= X)
                    {
                        log_message_line(bug_run_string(X +1, bug_term::horizon_line) +bug_run_string(level +1, BUG_T("┴")) +bug_run_string(38 -(X +level +1), bug_term::horizon_line));
                    }
                    else
                    {
                        log_message_line(BUG_T("┴") +bug_run_string(38, bug_term::horizon_line));
                    }
                }
#endif  //  defined(BUG_LANG_JP)
#if defined(BUG_LANG_EN)
                log_message_line(bug_run_string(79, bug_term::horizon_line));
                log_message_line(BUG_T("\t") +long_stamp);
                log_message_line(bug_run_string(79, bug_term::horizon_line));
#endif  //  defined(BUG_LANG_EN)
                return *this;
            }
            

        private:
            base_type & log_message_core(const bug_message & message)
            {
#if defined(BUG_LANG_JP)
                const bug_string level_branch       = BUG_T("├・");
#endif  //  defined(BUG_LANG_JP)
#if defined(BUG_LANG_EN)
                const bug_string level_branch       = BUG_T("-");
#endif  //  defined(BUG_LANG_EN)
                log_message_with_stamp(level_branch +message.get_full_message());
                return *this;
            }
            base_type & log_level_up_core(const bug_message & message)
            {
#if defined(BUG_LANG_JP)
                const bug_string level_up           = BUG_T("├┬");
#endif  //  defined(BUG_LANG_JP)
#if defined(BUG_LANG_EN)
                const bug_string level_up           = BUG_T("#-");
#endif  //  defined(BUG_LANG_EN)
                log_message_with_stamp(level_up +message.get_full_message());
                return *this;
            }
            base_type & log_level_down_core(const bug_message & message)
            {
#if defined(BUG_LANG_JP)
                const bug_string level_down         = BUG_T("└");
#endif  //  defined(BUG_LANG_JP)
#if defined(BUG_LANG_EN)
                const bug_string level_down         = BUG_T(".");
#endif  //  defined(BUG_LANG_EN)
                log_message_with_stamp(level_down +message.get_full_message());
                return *this;
            }

            this_type & log_message_with_stamp(const bug_string & message)
            {
#if defined(BUG_LANG_JP)
                const bug_string level_line         = BUG_T("│");
#endif  //  defined(BUG_LANG_JP)
#if defined(BUG_LANG_EN)
                const bug_string level_line         = BUG_T("|");
#endif  //  defined(BUG_LANG_EN)
                log_message_line(get_new_stamp() +bug_run_string(level, level_line) +message);
                return *this;
            }
            this_type & log_message_line(const bug_string & message)
            {
#if defined(BUG_SINGLE_THREAD) && !defined(BUG_MULTI_PROCESS)
                writer->write(message +bug_term::return_code);
#else
                writer->write(logger_id +message +bug_term::return_code);
#endif
                return *this;
            }
        };
        class bug_compact_tree_logger :public bug_logger
        {
        public:
            typedef bug_compact_tree_logger this_type;
            typedef bug_logger              base_type;
#if defined(__MWERKS__)
            typedef bug_clock_stamp_with_date stamp_with_date_type;
#else
            typedef bug_clock_stamp_ex_with_date stamp_with_date_type;
#endif

#if defined(BUG_MULTI_PROCESS) || defined(BUG_MULTI_THREAD)
            bug_string logger_id;
#endif
            bug_compact_tree_logger(bug_writer * a_writer = new bug_stream_writer, bug_stamp * a_stamp = new bug_default_stamp)
                :bug_logger(a_writer, a_stamp)
#if defined(BUG_MULTI_PROCESS) && defined(BUG_MULTI_THREAD)
                ,logger_id(bug_form(BUG_T("%d\t%d\t"), bug_get_process_id(), bug_get_thread_id()))
#elif defined(BUG_MULTI_PROCESS)
                ,logger_id(bug_form(BUG_T("%d\t"), bug_get_process_id()))
#elif defined(BUG_MULTI_THREAD)
                ,logger_id(bug_form(BUG_T("%d\t"), bug_get_thread_id()))
#endif
            {
                top_sign();
            }
            ~bug_compact_tree_logger() { bottom_sign(); }

            this_type & top_sign()
            {
                const bug_string long_stamp = stamp_with_date_type().get_stamp();
#if defined(BUG_LANG_JP)
                const int X = (int)((get_new_stamp().length() +1) /2 -1);
                if (BUG_T("") != long_stamp) {
                    log_message_line(BUG_T("┌") +bug_run_string(38, bug_term::horizon_line));
                    log_message_line(BUG_T("│") +long_stamp);

                    if (0 <= X) {
                        log_message_line(BUG_T("└") +bug_run_string(X, bug_term::horizon_line) +bug_run_string(level +1, BUG_T("┬")) +bug_run_string(38 -(X +level +1), bug_term::horizon_line));
                    } else {
                        log_message_line(BUG_T("├") +bug_run_string(38, bug_term::horizon_line));
                    }

                } else {

                    if (0 <= X) {
                        log_message_line(bug_run_string(X +1, bug_term::horizon_line) +bug_run_string(level +1, BUG_T("┬")) +bug_run_string(38 -(X +level +1), bug_term::horizon_line));
                    } else {
                        log_message_line(BUG_T("┬") +bug_run_string(38, bug_term::horizon_line));
                    }

                }
#endif  //  defined(BUG_LANG_JP)
#if defined(BUG_LANG_EN)
                log_message_line(bug_run_string(79, bug_term::horizon_line));
                log_message_line(BUG_T("\t") +long_stamp);
                log_message_line(bug_run_string(79, bug_term::horizon_line));
#endif  //  defined(BUG_LANG_EN)

                return *this;
            }
            this_type & bottom_sign()
            {
                const bug_string long_stamp = stamp_with_date_type().get_stamp();
#if defined(BUG_LANG_JP)
                const int X = (int)((get_new_stamp().length() +1) /2 -1);
                if (BUG_T("") != long_stamp)
                {
                    if (0 <= X)
                    {
                        log_message_line(BUG_T("┌") +bug_run_string(X, bug_term::horizon_line) +bug_run_string(level +1, BUG_T("┴")) +bug_run_string(38 -(X +level +1), bug_term::horizon_line));
                    }
                    else
                    {
                        log_message_line(BUG_T("├") +bug_run_string(38, bug_term::horizon_line));
                    }
                    log_message_line(BUG_T("│") +long_stamp);
                    log_message_line(BUG_T("└") +bug_run_string(38, bug_term::horizon_line));
                }
                else
                {
                    if (0 <= X)
                    {
                        log_message_line(bug_run_string(X +1, bug_term::horizon_line) +bug_run_string(level +1, BUG_T("┴")) +bug_run_string(38 -(X +level +1), bug_term::horizon_line));
                    }
                    else
                    {
                        log_message_line(BUG_T("┴") +bug_run_string(38, bug_term::horizon_line));
                    }
                }
#endif  //  defined(BUG_LANG_JP)
#if defined(BUG_LANG_EN)
                log_message_line(bug_run_string(79, bug_term::horizon_line));
                log_message_line(BUG_T("\t") +long_stamp);
                log_message_line(bug_run_string(79, bug_term::horizon_line));
#endif  //  defined(BUG_LANG_EN)
                return *this;
            }
            

        private:
            base_type & log_message_core(const bug_message & message)
            {
#if defined(BUG_LANG_JP)
                const bug_string level_branch       = BUG_T("・");
#endif  //  defined(BUG_LANG_JP)
#if defined(BUG_LANG_EN)
                const bug_string level_branch       = BUG_T("-");
#endif  //  defined(BUG_LANG_EN)
                log_message_with_stamp(level_branch +message.get_full_message());
                return *this;
            }
            base_type & log_level_up_core(const bug_message & message)
            {
                log_message_with_stamp(message.get_full_message());
                return *this;
            }
            base_type & log_level_down_core(const bug_message & message)
            {
                log_message_with_stamp(message.get_full_message());
                return *this;
            }

            this_type & log_message_with_stamp(const bug_string & message)
            {
#if defined(BUG_LANG_JP)
                const bug_string level_line         = BUG_T("│");
#endif  //  defined(BUG_LANG_JP)
#if defined(BUG_LANG_EN)
                const bug_string level_line         = BUG_T("|");
#endif  //  defined(BUG_LANG_EN)
                const bug_char * compact_level_mark[] =
                {
                    BUG_T(""),
                    BUG_T("-"),
                    BUG_T("="),
                };
                log_message_line(get_new_stamp() +level_line +bug_run_string(level/3, BUG_T("*")) +compact_level_mark[level%3] +message);
                return *this;
            }
            this_type & log_message_line(const bug_string & message)
            {
#if defined(BUG_SINGLE_THREAD) && !defined(BUG_MULTI_PROCESS)
                writer->write(message +bug_term::return_code);
#else
                writer->write(logger_id +message +bug_term::return_code);
#endif
                return *this;
            }
        };
        class bug_outline_logger :public bug_logger
        {
        public:
            typedef bug_outline_logger  this_type;
            typedef bug_logger          base_type;
#if defined(__MWERKS__)
            typedef bug_clock_stamp_with_date stamp_with_date_type;
#else
            typedef bug_clock_stamp_ex_with_date stamp_with_date_type;
#endif

#if defined(BUG_MULTI_PROCESS) || defined(BUG_MULTI_THREAD)
            bug_string logger_id;
#endif
            bug_string indent_base;
            
            bug_outline_logger(bug_string a_indent_base, bug_writer * a_writer = new bug_stream_writer, bug_stamp * a_stamp = new bug_default_stamp)
                :bug_logger(a_writer, a_stamp)
                ,indent_base(a_indent_base)
#if defined(BUG_MULTI_PROCESS) && defined(BUG_MULTI_THREAD)
                ,logger_id(bug_form(BUG_T("%d\t%d\t"), bug_get_process_id(), bug_get_thread_id()))
#elif defined(BUG_MULTI_PROCESS)
                ,logger_id(bug_form(BUG_T("%d\t"), bug_get_process_id()))
#elif defined(BUG_MULTI_THREAD)
                ,logger_id(bug_form(BUG_T("%d\t"), bug_get_thread_id()))
#endif
            {
                top_sign();
            }
            ~bug_outline_logger() { bottom_sign(); }

            this_type & top_sign()
            {
                log_message_line(stamp_with_date_type().get_stamp());
                return *this;
            }
            this_type & bottom_sign()
            {
                log_message_line(indent_base +stamp_with_date_type().get_stamp());
                return *this;
            }

        private:
            base_type & log_message_core(const bug_message & message)
            {
                log_message_with_stamp(message.get_full_message());
                return *this;
            }
            base_type & log_level_up_core(const bug_message & message)
            {
                log_message_with_stamp(message.get_full_message());
                return *this;
            }
            base_type & log_level_down_core(const bug_message & message)
            {
                log_message_with_stamp(message.get_full_message());
                return *this;
            }

            this_type & log_message_with_stamp(const bug_string & message)
            {
                log_message_line(bug_run_string(level +1, indent_base) +message +BUG_T("|") +get_new_stamp());
                return *this;
            }
            this_type & log_message_line(const bug_string & message)
            {
#if defined(BUG_SINGLE_THREAD) && !defined(BUG_MULTI_PROCESS)
                writer->write(message +bug_term::return_code);
#else
                writer->write(message +BUG_T("|") +logger_id +bug_term::return_code);
#endif
                return *this;
            }
        };

        
    ///////////////////////////////////////////////////////////////////////////
    //
    //  bug_profile_time_type
    //
    
    class bug_profile_time_type
    {
    public:
#if defined(__GNUC__)
        typedef int64_t value_type;
#else
        typedef __int64 value_type;
#endif
        typedef bug_profile_time_type this_type;

        value_type value;
        
        bug_profile_time_type(value_type a_value) :value(a_value) { }
        bug_profile_time_type(const this_type & a) :value(a.value) { }
        
        static bug_profile_time_type get_current_tick()
        {
            value_type result;
#if defined(__GNUC__)
            struct timeval tv;
            gettimeofday(&tv, NULL);
            result = tv.tv_sec;
            result *= 1000000;
            result += tv.tv_usec;
#else
            if (!QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER *>(&result)))
            {
                BUG_API_T(OutputDebugString)(BUG_T("QueryPerformanceCounter() is failure."));
            }
#endif
            return result;
        }
        static bug_profile_time_type get_by_msec(value_type msec)
        {
            return bug_profile_time_type
            (
                msec
                *get_tick_resolution()
                /1000
            );
        }
        
        static value_type get_tick_resolution()
        {
#if defined(__GNUC__)
            return 1000000;
#else
            value_type result;
            if (!QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER *>(&result)))
            {
                BUG_API_T(OutputDebugString)(BUG_T("QueryPerformanceFrequency() is failure."));
            }
            return result;
#endif
        }
        
        value_type get_sec() const
        {
            return value /get_tick_resolution();
        }
        value_type get_usec() const // without sec
        {
            const value_type tick_resolution = get_tick_resolution();
            const value_type scale = 1000000;
            return ((value %tick_resolution) *scale) /tick_resolution;
        }
        value_type get_total_msec() const // with sec
        {
            return (get_sec() *1000) +(get_usec() /1000);
        }
        
        this_type operator = (const this_type & a)
        {
            value = a.value;
            return *this;
        }
        this_type operator += (const this_type & a)
        {
            value += a.value;
            return *this;
        }
        this_type operator -= (const this_type & a)
        {
            value -= a.value;
            return *this;
        }
        this_type operator /= (const bug_sint64_type & a_value)
        {
            value /= a_value;
            return *this;
        }
        this_type operator + (const this_type & a) const
        {
            return value + a.value;
        }
        this_type operator - (const this_type & a) const
        {
            return value - a.value;
        }
        this_type operator / (const bug_sint64_type & a_value) const
        {
            return value / a_value;
        }
        
        bug_string get_string(const bug_string & a) const
        {
            if (0 <= value)
            {
                return bug_form
                (
                    BUG_T("%d.%06d"),
                    static_cast<int>(get_sec()),
                    static_cast<int>(get_usec())
                );
            }
            else
            {
                return BUG_T("-") +this_type(-value).get_string(a);
            }
        }
    };
    inline bool operator == (const bug_profile_time_type & a, const bug_profile_time_type & b)
    {
        return a.value == b.value;
    }
    inline bool operator != (const bug_profile_time_type & a, const bug_profile_time_type & b)
    {
        return a.value != b.value;
    }
    inline bool operator < (const bug_profile_time_type & a, const bug_profile_time_type & b)
    {
        return a.value < b.value;
    }
    inline bool operator <= (const bug_profile_time_type & a, const bug_profile_time_type & b)
    {
        return a.value <= b.value;
    }
    inline bool operator > (const bug_profile_time_type & a, const bug_profile_time_type & b)
    {
        return a.value > b.value;
    }
    inline bool operator >= (const bug_profile_time_type & a, const bug_profile_time_type & b)
    {
        return a.value >= b.value;
    }
    
    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  bug_profile_time_set, bug_profile_time_score, bug_profile_time_score_set
    //
    
    class bug_profile_time_score;
    class bug_profile_time_score_set;
    class bug_profiler;
    class bug_profile_scope;
    
    class bug_profile_time_set
    {
    
    friend class bug_profile_time_score;
    friend class bug_profiler;
    friend class bug_profile_scope;
    
    private:
        bug_profile_time_type whole_time;
        bug_profile_time_type bug_time;
        bug_profile_time_type work_time;
        
    public:
        typedef bug_profile_time_set this_type;

        bug_profile_time_set() :whole_time(0), bug_time(0), work_time(0) { }
        bug_profile_time_set(const this_type & a)
            :whole_time(a.whole_time), bug_time(a.bug_time), work_time(a.work_time) { }
        
        bug_profile_time_type get_whole_time() const
        {
            return whole_time;
        }
        bug_profile_time_type get_bug_time() const
        {
            return bug_time;
        }
        bug_profile_time_type get_work_time() const
        {
            return work_time;
        }
        
        this_type & operator += (const this_type & a)
        {
            whole_time += a.whole_time;
            bug_time += a.bug_time;
            work_time += a.work_time;
            return *this;
        }
        this_type & operator -= (const this_type & a)
        {
            whole_time -= a.whole_time;
            bug_time -= a.bug_time;
            work_time -= a.work_time;
            return *this;
        }
        this_type & operator /= (const bug_sint64_type & a)
        {
            whole_time /= a;
            bug_time /= a;
            work_time /= a;
            return *this;
        }
        this_type operator + (const this_type & a) const
        {
            this_type result(*this);
            result += a;
            return result;
        }
        this_type operator - (const this_type & a) const
        {
            this_type result(*this);
            result -= a;
            return result;
        }
        this_type operator / (const bug_sint64_type & a) const
        {
            this_type result(*this);
            result /= a;
            return result;
        }
        
        bug_string get_string(const bug_string & separetor) const
        {
            return
                get_whole_time().get_string(separetor)  +separetor
                +get_bug_time().get_string(separetor)   +separetor
                +get_work_time().get_string(separetor);
        }
        
        bug_profile_time_type get_core_value() const
        {
            return get_work_time();
        }
        friend bool operator < (const this_type & a, const this_type & b)
        {
            return a.get_core_value() < b.get_core_value();
        }
    };

    class bug_profile_time_score
    {
    
    friend class bug_profile_time_score_set;
    friend class bug_profiler;
    friend class bug_profile_scope;
    
    private:
        bug_profile_time_set self_time_set;
        bug_profile_time_set sub_time_set;
        
    public:
        typedef bug_profile_time_score this_type;
        
        bug_profile_time_score() :self_time_set(), sub_time_set() { }
        bug_profile_time_score(const this_type & a)
            :self_time_set(a.self_time_set), sub_time_set(a.sub_time_set) { }
        
        bug_profile_time_set get_all_time_set() const
        {
            bug_profile_time_set result(self_time_set);
            result.whole_time += sub_time_set.whole_time;
            result.bug_time += sub_time_set.bug_time;
            result.work_time += sub_time_set.work_time;
            return result;
        }
        bug_profile_time_set get_self_time_set() const
        {
            return self_time_set;
        }
        bug_profile_time_set get_sub_time_set() const
        {
            return sub_time_set;
        }
        
        this_type & operator += (const this_type & a)
        {
            self_time_set += a.self_time_set;
            sub_time_set += a.sub_time_set;
            return *this;
        }
        this_type & operator /= (const bug_sint64_type & a)
        {
            self_time_set /= a;
            sub_time_set /= a;
            return *this;
        }
        this_type operator + (const this_type & a) const
        {
            this_type result(*this);
            result += a;
            return result;
        }
        this_type operator / (const bug_sint64_type & a) const
        {
            this_type result(*this);
            result /= a;
            return result;
        }
        
        bug_string get_string(const bug_string & separetor) const
        {
            return
                get_all_time_set().get_string(separetor)    +separetor
                +get_self_time_set().get_string(separetor)  +separetor
                +get_sub_time_set().get_string(separetor);
        }
        
        bug_profile_time_set get_core_value() const
        {
            return get_all_time_set();
        }
        friend bool operator < (const this_type & a, const this_type & b)
        {
            return a.get_core_value() < b.get_core_value();
        }
    };

#if defined(__BORLANDC__) && 0x520 < __BORLANDC__
#   pragma warn -8026
#endif
    class bug_profile_time_score_set
    {
    private:
        bug_profile_time_score cumulative_total_score;
        bug_profile_time_score total_score;
        bug_string min_begin_stamp;
        bug_profile_time_score min_score;
        bug_string max_begin_stamp;
        bug_profile_time_score max_score;
        bug_sint64_type count;
        
    public:
        typedef bug_profile_time_score_set this_type;
        
        bug_profile_time_score_set()
            :cumulative_total_score(), total_score(), min_score(), max_score(), count(0) { }
        bug_profile_time_score_set(const this_type & a)
            :cumulative_total_score(a.cumulative_total_score),
            total_score(a.total_score),
            min_score(a.min_score),
            max_score(a.max_score),
            count(a.count) { }

        bug_profile_time_score get_cumulative_total_score() const
        {
            return cumulative_total_score;
        }
        bug_profile_time_score get_total_score() const
        {
            return total_score;
        }
        bug_profile_time_score get_min_score() const
        {
            return min_score;
        }
        bug_profile_time_score get_max_score() const
        {
            return max_score;
        }
        bug_profile_time_score get_average_score() const
        {
            if (count)
            {
                return get_total_score() /get_count();
            }
            else
            {
                return get_total_score();
            }
        }
        bug_sint64_type get_count() const
        {
            return count;
        }
        
        bug_string get_string(const bug_string & separetor) const
        {
            return
                get_cumulative_total_score().get_all_time_set().get_string(separetor)   +separetor
                +get_total_score().get_all_time_set().get_string(separetor)             +separetor
                +get_total_score().get_self_time_set().get_string(separetor)            +separetor
                +get_cumulative_total_score().get_sub_time_set().get_string(separetor)  +separetor
                +get_total_score().get_sub_time_set().get_string(separetor)             +separetor
                +bug_form(BUG_T("%d"), get_count())                                     +separetor
                +get_average_score().get_string(separetor)                              +separetor
                +min_begin_stamp                                                        +separetor
                +get_min_score().get_string(separetor)                                  +separetor
                +max_begin_stamp                                                        +separetor
                +get_max_score().get_string(separetor);
        }
        
        void add_score(bug_string a_begin_stamp, bug_profile_time_score a_time_score, const bug_profile_time_set & backup_self_time_set)
        {
            if (!get_count())
            {
                set_min_score(a_begin_stamp, a_time_score);
                set_max_score(a_begin_stamp, a_time_score);
                cumulative_total_score = a_time_score;
                total_score = a_time_score;
            }
            else
            {
                if (a_time_score < min_score)
                {
                    set_min_score(a_begin_stamp, a_time_score);
                }
                if (max_score < a_time_score)
                {
                    set_max_score(a_begin_stamp, a_time_score);
                }
                
                //  こちらはそのまま加算する
                cumulative_total_score += a_time_score;
                
                //  再帰呼び出しにより self として加算済みの時間が sub に再加算されるのを防ぐ処置。
                a_time_score.sub_time_set -= (total_score.get_self_time_set() -backup_self_time_set);
            
                total_score += a_time_score;
            }
            ++count;
        }
        
    private:
        void set_min_score(bug_string a_begin_stamp, bug_profile_time_score a_time_score)
        {
            min_begin_stamp = a_begin_stamp;
            min_score = a_time_score;
        }
        void set_max_score(bug_string a_begin_stamp, bug_profile_time_score a_time_score)
        {
            max_begin_stamp = a_begin_stamp;
            max_score = a_time_score;
        }
    };
#if defined(__BORLANDC__) && 0x520 < __BORLANDC__
#   pragma warn .8026
#endif


    ///////////////////////////////////////////////////////////////////////////
    //
    //  bug_timelimit
    //
    
    class  bug_timelimit
    {
    public:
        bug_message message;
        bug_profile_time_type start_tick;
        bug_profile_time_type bug_tick;
        bug_profile_time_type limit_tick;

        bug_timelimit(const bug_message & a_message, int timelimit, const bug_profile_time_type & a_start_tick = bug_profile_time_type::get_current_tick())
            :message(a_message), 
            start_tick(a_start_tick),
            bug_tick(0),
            limit_tick(bug_profile_time_type::get_by_msec(timelimit))
        {
        }
        bug_profile_time_type get_rest_tick(const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
        {
            return (start_tick +limit_tick +bug_tick) -a_current_tick;
        }
        void heart_beat(bug_logger & logger, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
        {
            if (get_rest_tick(a_current_tick) < 0)
            {
                logger.log_message(message.create(BUG_T("Time limit violation: ") +message.get_message()));
                TRICKLIB_BUG_TIMELIMIT_EXIT;
            }
        }
    };
    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  bug_profiler
    //
    
#if defined(__BORLANDC__) && 0x520 < __BORLANDC__
#   pragma warn -8026
#endif
    class bug_profiler :public bug_dummy_if
    {
    protected:
        bug_writer * profile_writer;
        bug_writer * coverage_writer;
		bug_writer * callgraph_writer;
		unsigned int level;
        int bug_scope_count;
        bug_profile_time_type bug_scope_begin_time;
        std::stack<bug_profile_time_score *> score_stack;
		std::stack<bug_message> scope_stack;
		std::map<bug_message, bug_profile_time_score_set> profile_db;
		std::map<std::pair<bug_message, bug_message>, bug_sint64_type> callgraph_db;
		std::stack<bug_timelimit *> timelimit_stack;
        
        bug_profile_time_type overall_start_time;
        bug_profile_time_score overall_time_score;
        
    public:
        typedef bug_profiler this_type;

#if defined(_MSC_VER) && _MSC_VER <= 1200
        bug_profiler(const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
            :profile_writer(new bug_stream_writer()),
            coverage_writer(NULL),
			callgraph_writer(NULL),
			level(0),
            bug_scope_count(0),
            bug_scope_begin_time(0),
            overall_start_time(a_current_tick)
        {
            begin_bug_time(a_current_tick);
			push_time_score(bug_message::get_overall(), &overall_time_score);
            end_bug_time();
        }
        bug_profiler(bug_writer * a_profile_writer, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
#else
        bug_profiler(bug_writer * a_profile_writer = new bug_stream_writer(), const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
#endif
            :profile_writer(a_profile_writer),
            coverage_writer(NULL),
			callgraph_writer(NULL),
			level(0),
            bug_scope_count(0),
            bug_scope_begin_time(0),
            overall_start_time(a_current_tick)
        {
            begin_bug_time(a_current_tick);
			push_time_score(bug_message::get_overall(), &overall_time_score);
            end_bug_time();
        }
        bug_profiler(bug_writer * a_profile_writer, bug_writer * a_coverage_writer, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
            :profile_writer(a_profile_writer),
            coverage_writer(a_coverage_writer),
			callgraph_writer(NULL),
			level(0),
            bug_scope_count(0),
            bug_scope_begin_time(0),
            overall_start_time(a_current_tick)
        {
            begin_bug_time(a_current_tick);
			push_time_score(bug_message::get_overall(), &overall_time_score);
            end_bug_time();
        }
		bug_profiler(bug_writer * a_profile_writer, bug_writer * a_coverage_writer, bug_writer * a_callgraph_writer, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
			:profile_writer(a_profile_writer),
			coverage_writer(a_coverage_writer),
			callgraph_writer(a_callgraph_writer),
			level(0),
			bug_scope_count(0),
			bug_scope_begin_time(0),
			overall_start_time(a_current_tick)
		{
			begin_bug_time(a_current_tick);
			push_time_score(bug_message::get_overall(), &overall_time_score);
			end_bug_time();
		}
        virtual ~bug_profiler()
        {
            delete profile_writer;
            delete coverage_writer;
			delete callgraph_writer;
		}

        void push_timelimit(bug_timelimit * i)
        {
            if (this)
            {
                const bug_profile_time_type current_tick = bug_profile_time_type::get_current_tick();
                if (timelimit_stack.empty() || i->get_rest_tick(current_tick) < timelimit_stack.top()->get_rest_tick(current_tick))
                {
                    timelimit_stack.push(i);
                }
            }
        }
        void pop_timelimit(bug_timelimit * i)
        {
            if (this)
            {
                if (!timelimit_stack.empty() && i == timelimit_stack.top())
                {
                    timelimit_stack.pop();
                }
            }
        }
        void timelimit_heart_beat(bug_logger & logger, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
        {
            if (this)
            {
                if (!timelimit_stack.empty())
                {
                    timelimit_stack.top()->heart_beat(logger, a_current_tick);
                }
            }
            else
            {
                if (!timelimit_stack.empty())
                {
                    logger.log_message(timelimit_stack.top()->message.create(BUG_T("time limit require profiler: ") +timelimit_stack.top()->message.get_message()));
                    TRICKLIB_BUG_TIMELIMIT_EXIT;
                }
            }
        }
        
        static bug_profiler & get_instance()
        {
            return *(bugbeard::bug_thread_local_storage<this_type>::get_target());
        }
        
		void push_time_score(const bug_message & a_message, bug_profile_time_score * a_time_score, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
        {
            if (this)
            {
                if (0 < bug_scope_count)
                {
                    if (false == score_stack.empty())
                    {
                        if (bug_scope_begin_time < a_current_tick)
                        {
                            score_stack.top()->self_time_set.bug_time += a_current_tick -bug_scope_begin_time;
                            bug_scope_begin_time = a_current_tick;
                        }
                    }
					if (false == scope_stack.empty())
					{
						++callgraph_db[std::pair<bug_message, bug_message>(scope_stack.top(), a_message)];
					}
				}
                score_stack.push(a_time_score);
				scope_stack.push(a_message);
			}
        }
        const bug_profile_time_set get_current_self_time_set(const bug_message & a_message)
        {
            return profile_db[a_message].get_total_score().get_self_time_set();
        }
        void add_time_score(const bug_message & a_message, const bug_string a_start_stamp, bug_profile_time_score & a_time_score, const bug_profile_time_set & backup_self_time_set)
        {
            if (this)
            {
                if (false == score_stack.empty())
                {
                    score_stack.top()->sub_time_set += a_time_score.get_all_time_set();
                }
                profile_db[a_message].add_score(a_start_stamp, a_time_score, backup_self_time_set);
			}
        }
        void pop_time_score(const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
        {
            if (this)
            {
                if (false == score_stack.empty())
                {
                    bug_profile_time_score * current_time_score = score_stack.top();
                    if (0 < bug_scope_count)
                    {
                        if (bug_scope_begin_time < a_current_tick)
                        {
                            current_time_score->self_time_set.bug_time += a_current_tick -bug_scope_begin_time;
                            bug_scope_begin_time = a_current_tick;
                        }
                    }
                    score_stack.pop();
					scope_stack.pop();
				}
            }
        }

        
        void begin_bug_time(const bug_profile_time_type & a_current_tick)
        {
            if (this)
            {
                if (0 == bug_scope_count++)
                {
                    bug_scope_begin_time = a_current_tick;
                }
            }
        }
        void end_bug_time()
        {
            if (this)
            {
                if (0 == --bug_scope_count)
                {
                    if (false == score_stack.empty())
                    {
                        bug_profile_time_type & bug_time = score_stack.top()->self_time_set.bug_time;
                        bug_time += bug_profile_time_type::get_current_tick() -bug_scope_begin_time;
                    }
                }
            }
        }
        
    protected:
        void overall_scope_end(const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
        {
            begin_bug_time(a_current_tick);
            pop_time_score();
            overall_time_score.self_time_set.whole_time = bug_profile_time_type::get_current_tick() -overall_start_time -overall_time_score.get_sub_time_set().get_whole_time();
            overall_time_score.self_time_set.work_time = overall_time_score.get_self_time_set().get_whole_time() -overall_time_score.get_self_time_set().get_bug_time();
			add_time_score(bug_message::get_overall(), bug_term::overall_scope_label, overall_time_score, bug_profile_time_set());
            end_bug_time();
        }
    };
#if defined(__BORLANDC__) && 0x520 < __BORLANDC__
#   pragma warn .8026
#endif

        class bug_tsv_profiler :public bug_profiler
        {
        public:
            typedef bug_tsv_profiler  this_type;
            typedef bug_profiler      base_type;

			bug_tsv_profiler
			(
				bug_writer * a_profile_writer = new bug_stream_writer,
				bug_writer * a_coverage_writer = NULL,
				bug_writer * a_callgraph_writer = NULL
			)
				:bug_profiler
				(
					a_profile_writer,
					a_coverage_writer,
					a_callgraph_writer
				)
            {
            }
            ~bug_tsv_profiler()
            {
                overall_scope_end();
                if (profile_writer)
                {
                    output_profile();
                }
                if (coverage_writer)
                {
                    make_coverage_data();
                    output_coverage();
                }
				if (callgraph_writer)
				{
					output_callgraph();
				}
			}
            void output_profile()
            {
#if !defined(BUG_WITHOUT_TSV_PROFILE_HEADER)
                output_profile_header();
#endif // !defined(BUG_WITHOUT_TSV_PROFILE_HEADER)
                for
                (
                    std::map<bug_message, bug_profile_time_score_set>::iterator i = profile_db.begin();
                    i != profile_db.end();
                    ++i
                )
                {
                    output_profile_core(i->first, i->second);
                }
            }
#if !defined(BUG_WITHOUT_TSV_PROFILE_HEADER)
            base_type & output_profile_header()
            {
                const bug_string separetor = BUG_T("\t");
                profile_writer->write
                (
#if defined(BUG_MULTI_PROCESS)
                    bug_term::process_id_labe +separetor +
#endif
#if defined(BUG_MULTI_THREAD)
                    bug_term::thread_id_label +separetor +
#endif
#if !defined(BUG_WITHOUT_LOCATION_INFO)
                    bug_term::file_label +separetor +
                    bug_term::line_label +separetor +
#if defined(BUG_FUNCTION_NAME)
                    bug_term::function_label +separetor +
#endif
#endif
                    bug_term::scope_label +separetor +
                    bug_term::cumulative_total_all_whole_time_label +separetor +
                    bug_term::cumulative_total_all_bug_time_label +separetor +
                    bug_term::cumulative_total_all_work_time_label +separetor +
                    bug_term::total_all_whole_time_label +separetor +
                    bug_term::total_all_bug_time_label +separetor +
                    bug_term::total_all_work_time_label +separetor +
                    bug_term::total_self_whole_time_label +separetor +
                    bug_term::total_self_bug_time_label +separetor +
                    bug_term::total_self_work_time_label +separetor +
                    bug_term::cumulative_total_sub_whole_time_label +separetor +
                    bug_term::cumulative_total_sub_bug_time_label +separetor +
                    bug_term::cumulative_total_sub_work_time_label +separetor +
                    bug_term::total_sub_whole_time_label +separetor +
                    bug_term::total_sub_bug_time_label +separetor +
                    bug_term::total_sub_work_time_label +separetor +
                    bug_term::call_count_label +separetor +
                    bug_term::average_all_whole_time_label +separetor +
                    bug_term::average_all_bug_time_label +separetor +
                    bug_term::average_all_work_time_label +separetor +
                    bug_term::average_self_whole_time_label +separetor +
                    bug_term::average_self_bug_time_label +separetor +
                    bug_term::average_self_work_time_label +separetor +
                    bug_term::average_sub_whole_time_label +separetor +
                    bug_term::average_sub_bug_time_label +separetor +
                    bug_term::average_sub_work_time_label +separetor +
                    bug_term::min_time_stamp_label +separetor +
                    bug_term::min_all_whole_time_label +separetor +
                    bug_term::min_all_bug_time_label +separetor +
                    bug_term::min_all_work_time_label +separetor +
                    bug_term::min_self_whole_time_label +separetor +
                    bug_term::min_self_bug_time_label +separetor +
                    bug_term::min_self_work_time_label +separetor +
                    bug_term::min_sub_whole_time_label +separetor +
                    bug_term::min_sub_bug_time_label +separetor +
                    bug_term::min_sub_work_time_label +separetor +
                    bug_term::max_time_stamp_label +separetor +
                    bug_term::max_all_whole_time_label +separetor +
                    bug_term::max_all_bug_time_label +separetor +
                    bug_term::max_all_work_time_label +separetor +
                    bug_term::max_self_whole_time_label +separetor +
                    bug_term::max_self_bug_time_label +separetor +
                    bug_term::max_self_work_time_label +separetor +
                    bug_term::max_sub_whole_time_label +separetor +
                    bug_term::max_sub_bug_time_label +separetor +
                    bug_term::max_sub_work_time_label +bug_term::return_code
                );
                return *this;
            }
#endif // !defined(BUG_WITHOUT_TSV_PROFILE_HEADER)
            base_type & output_profile_core(const bug_message & a_message, const bug_profile_time_score_set & a_time_score_set)
            {
                const bug_string separetor = BUG_T("\t");
                profile_writer->write
                (
#if defined(BUG_MULTI_PROCESS) && defined(BUG_MULTI_THREAD)
                    bug_form(BUG_T("%d\t%d\t"), bug_get_process_id(), bug_get_thread_id())
#elif defined(BUG_MULTI_PROCESS)
                    bug_form(BUG_T("%d\t"), bug_get_process_id())
#elif defined(BUG_MULTI_THREAD)
                    bug_form(BUG_T("%d\t"), bug_get_thread_id())
#else
                    BUG_T("")
#endif
#if !defined(BUG_WITHOUT_LOCATION_INFO)
                    +a_message.get_file()
                    +bug_form(BUG_T("\t%d\t"), a_message.get_line())
#if defined(BUG_FUNCTION_NAME)
                    +a_message.get_function_name()
                    +BUG_T("\t")
#endif
#endif
                    +a_message.get_message() +separetor
                    +a_time_score_set.get_string(separetor)
                    +bug_term::return_code
                );
                return *this;
            }
            
            void make_coverage_data()
            {
                const size_t if_statement_term_length = bug_term::if_statement_term.length();
                const size_t false_result_term_length = bug_term::false_result_term.length();
                const size_t true_result_term_length  = bug_term::true_result_term.length();
                
                for
                (
                    std::map<bug_message, bug_profile_time_score_set>::iterator i = profile_db.begin();
                    i != profile_db.end();
                    ++i
                )
                {
                    const bug_string scope_name = i->first.get_message();
                    if (bug_term::if_statement_term == scope_name.substr(0, if_statement_term_length))
                    {
                        const size_t scope_name_length = scope_name.length();
                        if (bug_term::false_result_term == scope_name.substr(scope_name_length -false_result_term_length))
                        {
                            profile_db[i->first.create(scope_name.substr(0, scope_name_length -false_result_term_length) +bug_term::true_result_term)];
                        }
                        else
                        if (bug_term::true_result_term == scope_name.substr(scope_name_length -true_result_term_length))
                        {
                            profile_db[i->first.create(scope_name.substr(0, scope_name_length -true_result_term_length) +bug_term::false_result_term)];
                        }
                    }
                }
            }
            void output_coverage()
            {
                const size_t if_statement_term_length = bug_term::if_statement_term.length();
                
#if !defined(BUG_WITHOUT_TSV_COVERAGE_HEADER)
                output_coverage_header();
#endif // !defined(BUG_WITHOUT_TSV_COVERAGE_HEADER)
                for
                (
                    std::map<bug_message, bug_profile_time_score_set>::iterator i = profile_db.begin();
                    i != profile_db.end();
                    ++i
                )
                {
                    if (bug_term::if_statement_term == i->first.get_message().substr(0, if_statement_term_length))
                    {
                        output_coverage_core(i->first, i->second);
                    }
                }
            }
#if !defined(BUG_WITHOUT_TSV_COVERAGE_HEADER)
            base_type & output_coverage_header()
            {
                const bug_string separetor = BUG_T("\t");
                coverage_writer->write
                (
#if !defined(BUG_WITHOUT_LOCATION_INFO)
                    bug_term::file_label +separetor +
                    bug_term::line_label +separetor +
#if defined(BUG_FUNCTION_NAME)
                    bug_term::function_label +separetor +
#endif
#endif
                    bug_term::scope_label +separetor +
                    bug_term::call_count_label +bug_term::return_code
                );
                return *this;
            }
#endif // !defined(BUG_WITHOUT_TSV_COVERAGE_HEADER)
            base_type & output_coverage_core(const bug_message & a_message, const bug_profile_time_score_set & a_time_score_set)
            {
                const bug_string separetor = BUG_T("\t");
                coverage_writer->write
                (
#if defined(BUG_WITHOUT_LOCATION_INFO)
                    BUG_T("")
#else
                    a_message.get_file()
                    +bug_form(BUG_T("\t%d\t"), a_message.get_line())
#if defined(BUG_FUNCTION_NAME)
                    +a_message.get_function_name()
                    +BUG_T("\t")
#endif
#endif
                    +a_message.get_message() +separetor
                    +bug_form(BUG_T("%") BUG_T(BUG_FORM_I64) BUG_T("d"), a_time_score_set.get_count())
                    +bug_term::return_code
                );
                return *this;
            }
			void output_callgraph()
			{
#if !defined(BUG_WITHOUT_TSV_CALLGRAPH_HEADER)
				output_callgraph_header();
#endif // !defined(BUG_WITHOUT_TSV_CALLGRAPH_HEADER)
				for
					(
					std::map<std::pair<bug_message, bug_message>, bug_sint64_type>::iterator i = callgraph_db.begin();
					i != callgraph_db.end();
					++i
					)
				{
					output_callgraph_core(i->first.first, i->first.second, i->second);
				}
			}
#if !defined(BUG_WITHOUT_TSV_CALLGRAPH_HEADER)
			base_type & output_callgraph_header()
			{
				const bug_string separetor = BUG_T("\t");
				callgraph_writer->write
					(
#if !defined(BUG_WITHOUT_LOCATION_INFO)
					bug_term::caller_label + bug_term::file_label + separetor +
					bug_term::caller_label + bug_term::line_label + separetor +
#if defined(BUG_FUNCTION_NAME)
					bug_term::caller_label + bug_term::function_label + separetor +
#endif
#endif
					bug_term::caller_label + bug_term::scope_label + separetor +
					bug_term::call_count_label + separetor +
#if !defined(BUG_WITHOUT_LOCATION_INFO)
					bug_term::callee_label + bug_term::file_label + separetor +
					bug_term::callee_label + bug_term::line_label + separetor +
#if defined(BUG_FUNCTION_NAME)
					bug_term::callee_label + bug_term::function_label + separetor +
#endif
#endif
					bug_term::callee_label + bug_term::scope_label + bug_term::return_code
					);
				return *this;
			}
#endif // !defined(BUG_WITHOUT_TSV_CALLGRAPH_HEADER)
			base_type & output_callgraph_core(const bug_message & caller_message, const bug_message & callee_message, const bug_sint64_type & a_call_count)
			{
				const bug_string separetor = BUG_T("\t");
				callgraph_writer->write
					(
#if defined(BUG_WITHOUT_LOCATION_INFO)
					BUG_T("")
#else
					caller_message.get_file()
					+ bug_form(BUG_T("\t%d\t"), caller_message.get_line())
#if defined(BUG_FUNCTION_NAME)
					+caller_message.get_function_name()
					+ BUG_T("\t")
#endif
#endif
					+ caller_message.get_message() + separetor

					+ bug_form(BUG_T("%") BUG_T(BUG_FORM_I64) BUG_T("d"), a_call_count) + separetor

#if defined(BUG_WITHOUT_LOCATION_INFO)
					+BUG_T("")
#else
					+callee_message.get_file()
					+ bug_form(BUG_T("\t%d\t"), callee_message.get_line())
#if defined(BUG_FUNCTION_NAME)
					+callee_message.get_function_name()
					+ BUG_T("\t")
#endif
#endif
					+ callee_message.get_message() + separetor

					+ bug_term::return_code
					);
				return *this;
			}
		};
		

    ///////////////////////////////////////////////////////////////////////////
    //
    //  bug_bug_time_scope
    //

#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable:4512)
#endif
    class bug_bug_time_scope
    {
    public:
        bug_profiler & profiler;
        bug_bug_time_scope(const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
            :profiler(bugbeard::bug_profiler::get_instance())
        {
            profiler.begin_bug_time(a_current_tick);
        }
        ~bug_bug_time_scope()
        {
            profiler.end_bug_time();
        }
    };
#if defined(_MSC_VER)
#   pragma warning(pop)
#endif
    
    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  bug_profile_scope
    //
    
#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable:4512)
#endif
    class bug_profile_scope :public bug_smart_ptr_ref_cnt
    {
    public:
        bug_profiler & profiler;
        const bug_string start_stamp;
        bug_profile_time_type start_time;
        bug_profile_time_score time_score;
        bug_profile_time_set backup_self_time_set;
        const bug_message message;
        
        bug_profile_scope(bug_logger & a_logger, const bug_message & a_message, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
            :profiler(bugbeard::bug_profiler::get_instance()), start_stamp(a_logger.get_last_stamp()), start_time(a_current_tick), time_score(), message(a_message)
        {
            bug_bug_time_scope bug_time_scope(a_current_tick);
			profiler.push_time_score(a_message, &time_score, a_current_tick);
            backup_self_time_set = profiler.get_current_self_time_set(message);
            profiler.timelimit_heart_beat(a_logger, a_current_tick);
        }
        ~bug_profile_scope()
        {
            const bug_profile_time_type current_tick = bug_profile_time_type::get_current_tick();
            bug_bug_time_scope bug_time_scope(current_tick);
            profiler.pop_time_score(current_tick);
            time_score.self_time_set.whole_time = current_tick -start_time -time_score.get_sub_time_set().get_whole_time();
            time_score.self_time_set.work_time = time_score.get_self_time_set().get_whole_time() -time_score.get_self_time_set().get_bug_time();
            profiler.add_time_score(message, start_stamp, time_score, backup_self_time_set);
        }
    };
#if defined(_MSC_VER)
#   pragma warning(pop)
#endif

    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  bug_element
    //

#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable:4512)
#endif
    class bug_element
    {
    private:
        mutable bool scoped;
        bool leveled;
        bug_message down_message;
    protected:
        bug_logger & logger;
        bug_smart_ptr<bug_profile_scope> profile_scope;
    public:
        bug_element(bug_logger & a_logger, bool a_leveled, const bug_message & a_message, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
            :scoped(true), leveled(a_leveled), logger(a_logger)
        {
            bug_bug_time_scope bug_time_scope(a_current_tick);
            if (leveled)
            {
                profile_scope = new bug_profile_scope(a_logger, a_message, a_current_tick);
                // ↑この行は元々 logger.log_level_up(up_message); の下であったが、
                //  その位置では Watcom C++ では異常終了を招くことがあるのでこの位置
                //  へ移動した。この問題は恐らく Watcom C++ のバグだと思われる。
                bug_string  core_message    = a_message.get_message();
                bug_message up_message      = a_message.create(bug_term::begin_prefix   +core_message);
                            down_message    = a_message.create(bug_term::end_prefix     +core_message);
                logger.log_level_up(up_message);
            }
            else
            {
                down_message = a_message;
            }
        }
#if 0 // 廃止
        bug_element(bug_logger & a_logger, const bug_message & a_up_message, const bug_message & a_down_message, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
            :scoped(true), leveled(true), logger(a_logger), down_message(a_down_message)
        {
            bug_bug_time_scope bug_time_scope(a_current_tick);
            logger.log_level_up(a_up_message);
        }
#endif
        bug_element(bug_logger & a_logger, const bug_dummy_if &) :scoped(false), leveled(false), logger(a_logger) { }
        bug_element(const bug_element & a)
            :scoped(a.scoped)
            ,leveled(a.leveled)
            ,logger(a.logger)
            ,down_message(a.down_message)
        {
            a.scoped = false;
        }
        ~bug_element()
        {
            bug_bug_time_scope bug_time_scope;
            close();
            profile_scope = NULL;
        }
        void close()
        {
            if (scoped)
            {
                if (leveled)
                {
                    logger.log_level_down(down_message);
                }
                else
                {
                    logger.log_message(down_message);
                }
                scoped = false;
            }
        }
    };
    class bug_scope :public bug_element
    {
    public:
        bug_scope(bug_logger & a_logger, const bug_message & a_message, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
            :bug_element(a_logger, true, a_message, a_current_tick) { }
#if 0 // 廃止
        bug_scope(bug_logger & a_logger, const bug_message & a_up_message, const bug_message & a_down_message)
            :bug_element(a_logger, a_up_message, a_down_message) { }
#endif
    };
    class bug_scope_with_timelimit :public bug_scope
    {
        bug_timelimit timelimit;
    public:
        bug_scope_with_timelimit(bug_logger & a_logger, const bug_message & a_message, int timelimit_ms, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
            :bug_scope(a_logger, a_message, a_current_tick),
            timelimit(a_message, timelimit_ms, a_current_tick)
        {
            profile_scope->profiler.push_timelimit(&timelimit);
        }
        ~bug_scope_with_timelimit()
        {
            profile_scope->profiler.pop_timelimit(&timelimit);
        }
    };
    class bug_scope_out :public bug_element
    {
    public:
        bug_scope_out(bug_logger & a_logger, const bug_message & a_down_message)
            :bug_element(a_logger, false, a_down_message) { }
    };
    class bug_new_core :public bug_scope
    {
    public:
        bug_new_core(bug_logger & a_logger, const bug_message & a_message)
            :bug_scope(a_logger, a_message) { }
        operator bool () const
        {
            return false;
        }
    };
    class bug_if_core :public bug_dummy_if, protected bug_element
    {
        const bool result;
    public:
        bug_if_core(bug_logger & a_logger, const bug_message & a_message, const bool & a_result)
            :bug_element(a_logger, true, a_message.create(a_message.get_message() +bug_term::bool_result_term(a_result))), result(a_result) { }
#if defined(__BORLANDC__) && __BORLANDC__ < 0x0560
        bug_if_core(bug_logger & a_logger, const bug_message & a_message, const void * a_result)
            :bug_element(a_logger, true, a_message.create(a_message.get_message() +bug_term::bool_result_term(a_result))), result(a_result) { }
#endif
        bug_if_core(bug_logger & a_logger, const bug_message &, const bug_dummy_if & a)
            :bug_element(a_logger, a), result(false) { }
        bug_if_core(bug_logger & a_logger, const bug_message &, const bug_element & a)
            :bug_element(a), result(false) { a_logger; }
        bug_if_core(const bug_if_core & a)
            :bug_element(a), result(a.result) { }
        operator const bool & () const
        {
            return result;
        }
    };
#if defined(BUG_DISABLED_WHILE_SCOPE)
    class bug_while_core :public bug_dummy_if
    {
        const bool result;
        void log_message(bug_logger & a_logger, const bug_message & a_message)
        {
            a_logger.log_message(a_message.create(a_message.get_message() +bug_term::bool_result_term(result)));
        }
    public:
        bug_while_core(bug_logger & a_logger, const bug_message & a_message, const bool & a_result, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
            :result(a_result)
        {
            bug_bug_time_scope bug_time_scope(a_current_tick);
            log_message(a_logger, a_message);
        }
        bug_while_core(bug_logger & a_logger, const bug_message & a_message, const void * a_result, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
            :result(NULL != a_result)
        {
            bug_bug_time_scope bug_time_scope(a_current_tick);
            log_message(a_logger, a_message);
        }
        bug_while_core(const bug_while_core & a)
            :result(a.result) { }
        operator const bool &() const
        {
            return result;
        }
    };
#else
    typedef bug_if_core bug_while_core;
#endif
    class bug_switch_core :public bug_dummy_if, protected bug_element
    {
        const int result;
    public:
#if defined(BUG_DISABLED_SWITCH_SCOPE)
        bug_switch_core(bug_logger & a_logger, const bug_message & a_message, const int & a_result, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
            :bug_element(a_logger, bug_dummy_if()), result(a_result)
        {
            bug_bug_time_scope bug_time_scope(a_current_tick);
            logger.log_message(a_message.create(a_message.get_message() +bug_encode_value(result)));
        }
#else
        bug_switch_core(bug_logger & a_logger, const bug_message & a_message, const int & a_result)
            :bug_element(a_logger, true, a_message.create(a_message.get_message() +bug_encode_value(result))), result(a_result) { }
#endif
        bug_switch_core(bug_logger & a_logger, const bug_message &, const bug_dummy_if & a)
            :bug_element(a_logger, a), result(false) { }
        bug_switch_core(bug_logger & a_logger, const bug_message &, const bug_element & a)
            :bug_element(a), result(false) { a_logger; }
        bug_switch_core(const bug_switch_core & a)
            :bug_element(a), result(a.result) { }
#if defined(__MWERKS__)
        operator const int () const
#else
        operator const int & () const
#endif
        {
            return result;
        }
    };
#if defined(BUG_ENABLED_CPP11_OR_LATER)
    template<class value_T>
    class bug_switch_core_ex :public bug_dummy_if, protected bug_element
    {
        const value_T result;
    public:
        bug_switch_core_ex(bug_logger & a_logger, const bug_message & a_message, const value_T & a_result)
            :bug_element(a_logger, true, a_message.create(a_message.get_message() +bug_encode_value(result))), result(a_result) { }
        //bug_switch_core_ex(bug_logger & a_logger, const bug_message &, const bug_dummy_if & a)
        //    :bug_element(a_logger, a), result(false) { }
        //bug_switch_core_ex(bug_logger & a_logger, const bug_message &, const bug_element & a)
        //    :bug_element(a), result(false) { a_logger; }
        bug_switch_core_ex(const bug_switch_core_ex<value_T> & a)
            :bug_element(a), result(a.result) { }
            
        operator const value_T & () const
        {
            return result;
        }
    };
    inline bug_switch_core bug_switch_helper(bug_logger & a_logger, const bug_message & dummy_message, const bug_dummy_if & a)
    {
        return bug_switch_core(a_logger, dummy_message, a);
    }
    inline bug_switch_core bug_switch_helper(bug_logger & a_logger, const bug_message & dummy_message, const bug_element & a)
    {
        return bug_switch_core(a_logger, dummy_message, a);
    }
    inline bug_switch_core bug_switch_helper(bug_logger & a_logger, const bug_message & dummy_message, const bug_scope_out & a)
    {
        return bug_switch_core(a_logger, dummy_message, a);
    }
    template<class value_T>
    inline bug_switch_core_ex<value_T> bug_switch_helper(bug_logger & a_logger, const bug_message & a_message, const value_T & a_result)
    {
        return bug_switch_core_ex<value_T>(a_logger, a_message, a_result);
    }
    inline bug_switch_core bug_switch_helper(const bug_switch_core & a)
    {
        return a;
    }
    template<class value_T>
    inline bug_switch_core_ex<value_T> bug_switch_helper(const bug_switch_core_ex<value_T> & a)
    {
        return a;
    }
#endif
    
#if defined(_MSC_VER)
#   pragma warning(pop)
#endif


    ///////////////////////////////////////////////////////////////////////////
    //
    //  各種情報のログ出力
    //

    //  [BUG]汎用ログ出力
    inline bug_logger & bug_log_message(bug_logger & a_logger, const bug_message & message, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
    {
        bug_bug_time_scope bug_time_scope(a_current_tick);
        a_logger.log_message(message);
        return a_logger;
    }
    
    //  [BUG]コンパイル情報のログ出力
    inline void bug_compile_info(bug_logger & a_logger, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
    {
        bug_bug_time_scope bug_time_scope(a_current_tick);
        bug_scope current_scope(a_logger, BUG_MSG(BUG_T("Compile Information")));
        //  [BUG]コンパイラ情報のログ出力
        a_logger.log_message(BUG_MSG(BUG_T("Compiler:") BUG_T(BUG_COMPILER_NAME) BUG_T("(") BUG_T(BUG_COMPILER_VERSION) BUG_T(")")));
        //  [BUG]コンパイル日時のログ出力
        a_logger.log_message(BUG_MSG(BUG_T("Compile Date:") BUG_T(__DATE__) BUG_T(" / Compile Time:") BUG_T(__TIME__)));
    }

    //  [BUG]コマンドライン引数のログ出力
    inline void bug_arg_info(bug_logger & a_logger, int argc, bug_char * args[], const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
    {
        bug_bug_time_scope bug_time_scope(a_current_tick);
        bug_scope current_scope(a_logger, BUG_MSG(BUG_T("Commandline Argument Information")));
        a_logger.log_message(BUG_MSG(BUG_VAL(argc)));
        for(int i = 0; i < argc; ++i)
        {
            a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("args[%d]:%s"), i, args[i])));
        }
    }

#if defined(BUG_MS_WINDOWS)
    //  [BUG]Windowsシステム情報のログ出力
    inline void bug_windows_system_info(bug_logger & a_logger, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
    {
        bug_bug_time_scope bug_time_scope(a_current_tick);
        bug_scope current_scope(a_logger, BUG_MSG(BUG_T("Windows System Information")));
        
        typedef void (WINAPI * PGNSI)(LPSYSTEM_INFO);
        SYSTEM_INFO si;
        
        PGNSI pGNSI = (PGNSI)GetProcAddress(GetModuleHandleA("kernel32.dll"), "GetNativeSystemInfo");
        if(NULL != pGNSI)
        {
            pGNSI(&si);
        }
        else
        {
            GetSystemInfo(&si);
        }
        a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("wProcessorArchitecture:%d"), si.wProcessorArchitecture)));
        a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("wReserved:%d"), si.wReserved)));
        a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("dwPageSize:%d"), si.dwPageSize)));
        a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("lpMinimumApplicationAddress:%08X"), si.lpMinimumApplicationAddress)));
        a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("lpMaximumApplicationAddress:%08X"), si.lpMaximumApplicationAddress)));
        a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("dwActiveProcessorMask:%d"), si.dwActiveProcessorMask)));
        a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("dwNumberOfProcessors:%d"), si.dwNumberOfProcessors)));
        a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("dwProcessorType:%d"), si.dwProcessorType)));
        a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("dwAllocationGranularity:%d"), si.dwAllocationGranularity)));
        a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("wProcessorLevel:%d"), si.wProcessorLevel)));
        a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("wProcessorRevision:%d"), si.wProcessorRevision)));
    }
    
    //  [BUG]Windowsバージョン情報のログ出力
    inline void bug_windows_version_info(bug_logger & a_logger, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
    {
        bug_bug_time_scope bug_time_scope(a_current_tick);
        bug_scope current_scope(a_logger, BUG_MSG(BUG_T("Windows Version Information")));
        bug_OSVERSIONINFO osvi;
#if 0x0500 <= WINVER
        a_logger.log_message(BUG_MSG(bug_get_winver(osvi)));
#endif // 0x0500 <= WINVER
        a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("OSVERSIONINFO dwMajorVersion:%d / dwMinorVersion:%d / dwBuildNumber:%d / dwPlatformId:%d / szCSDVersion:%s"), osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.dwBuildNumber, osvi.dwPlatformId, osvi.szCSDVersion)));
#if 0x0500 <= WINVER
        if (sizeof(OSVERSIONINFOEX) == osvi.dwOSVersionInfoSize)
        {
            a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("OSVERSIONINFOEX wServicePackMajor:%d / wServicePackMinor:%d / wSuiteMask:%d / wProductType:%d / wReserved:%d"), osvi.wServicePackMajor, osvi.wServicePackMinor, osvi.wSuiteMask, osvi.wProductType, osvi.wReserved)));
        }
#endif // 0x0500 <= WINVER
    }

    //  [BUG]ファイルハッシュ値のログ出力
#if 0x0500 <= WINVER
    inline void bug_file_hash(bug_logger & a_logger, const bug_char * file_name, const bug_char * hash_name = BUG_T("MD5"), ALG_ID algid = CALG_MD5, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
    {
        bug_bug_time_scope bug_time_scope(a_current_tick);
        BYTE hash[256];
        int hash_size = CalcHash(algid, OpenReadFile(file_name), hash, sizeof(hash));
        if (hash_size)
        {
            a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("file:\"%s\" / hash(%s):%s"), file_name, hash_name, bug_hex_encode(hash, hash_size).c_str())));
        }
        else
        {
            a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("file:\"%s\" / can not calc hash"), file_name)));
        }
    }
#endif // 0x0500 <= WINVER
    
    //  [BUG]各種モジュールバージョン情報のログ出力
    inline void bug_module_version_info(bug_logger & a_logger, const bug_char * dll_name, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
    {
        bug_bug_time_scope bug_time_scope(a_current_tick);
        bool has_version_information = false;
        
        bug_file_version_info file_version_info(dll_name);
        if(file_version_info.is_valid())
        {
            bug_translation_set translation_set;
            file_version_info.query_value_translation(&translation_set);
            
            for(size_t i = 0, size = translation_set.get_size(); i < size; ++i)
            {
                bug_string current = bug_form(BUG_T("module:\"%s\" / language:%04x%04x"), dll_name, translation_set[i].wLanguage, translation_set[i].wCodePage);
                const bug_char * param_list[] =
                {
                    BUG_T("FileDescription"),
                    BUG_T("FileVersion"),
                    BUG_T("ProductName"),
                    BUG_T("ProductVersion"),
                    BUG_T("CompanyName"),
                    BUG_T("OriginalFilename"),
                };
                for(size_t j = 0; j < (sizeof(param_list)/sizeof(param_list[0])); ++j)
                {
                    bug_string version_param_data;
                    if (file_version_info.query_value_string_file_info(translation_set[i], param_list[j], &version_param_data))
                    {
                        current += bug_form(BUG_T(" / %s:%s"), param_list[j], version_param_data.c_str());
                    }
                }
                
                a_logger.log_message(BUG_MSG(current));
                has_version_information = true;
            }
        }

        if (!has_version_information)
        {
            a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("module:\"%s\" / no version information"), dll_name)));
        }
    }
#if 0x0500 <= WINVER && !defined(BUG_DISABLED_PSAPI)
    inline void bug_enum_module_version_info(bug_logger & a_logger, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
    {
        bug_bug_time_scope bug_time_scope(a_current_tick);
        bug_scope current_scope(a_logger, BUG_MSG(BUG_T("Module Version Information")));
        DWORD      dwSize;
        HMODULE    modules[100];
        EnumProcessModules(GetCurrentProcess(), modules, sizeof(modules), &dwSize);
        for(size_t i = 0; i < dwSize / sizeof(HMODULE); ++i)
        {
            bug_char module_filename[MAX_PATH +1];
            GetModuleFileName(modules[i], module_filename, MAX_PATH);
            bug_module_version_info(a_logger, module_filename);
        }
    }
    inline void bug_enum_module_hash(bug_logger & a_logger, const bug_char * hash_name = BUG_T("MD5"), ALG_ID algid = CALG_MD5, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
    {
        bug_bug_time_scope bug_time_scope(a_current_tick);
        bug_scope current_scope(a_logger, BUG_MSG(BUG_T("Module Hash")));
        DWORD      dwSize;
        HMODULE    modules[100];
        EnumProcessModules(GetCurrentProcess(), modules, sizeof(modules), &dwSize);
        for(size_t i = 0; i < dwSize / sizeof(HMODULE); ++i)
        {
            bug_char module_filename[MAX_PATH +1];
            GetModuleFileName(modules[i], module_filename, MAX_PATH);
            bug_file_hash(a_logger, module_filename, hash_name, algid);
        }
    }
#endif // 0x0500 <= WINVER && !defined(BUG_DISABLED_PSAPI)
    
    //  [BUG]メモリ情報のログ出力
#if 0x0500 <= WINVER
    inline void bug_memory_info(bug_logger & a_logger, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
    {
        bug_bug_time_scope bug_time_scope(a_current_tick);
        bug_scope current_scope(a_logger, BUG_MSG(BUG_T("Memory Information")));
        MEMORYSTATUSEX mem_info;
        mem_info.dwLength = sizeof(mem_info);
        if (GlobalMemoryStatusEx(&mem_info))
        {
            a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("load:%d%%"), mem_info.dwMemoryLoad)));
            a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("TotalPhys:%s"), bug_binary_prefix(mem_info.ullTotalPhys, BUG_T("Byte")).c_str())));
            a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("AvailPhys:%s"), bug_binary_prefix(mem_info.ullAvailPhys, BUG_T("Byte")).c_str())));
            a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("Used-Phys:%s"), bug_binary_prefix(mem_info.ullTotalPhys -mem_info.ullAvailPhys, BUG_T("Byte")).c_str())));
            a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("TotalPageFile:%s"), bug_binary_prefix(mem_info.ullTotalPageFile, BUG_T("Byte")).c_str())));
            a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("AvailPageFile:%s"), bug_binary_prefix(mem_info.ullAvailPhys, BUG_T("Byte")).c_str())));
            a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("Used-PageFile:%s"), bug_binary_prefix(mem_info.ullTotalPageFile -mem_info.ullAvailPhys, BUG_T("Byte")).c_str())));
            a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("TotalVirtual:%s"), bug_binary_prefix(mem_info.ullTotalVirtual, BUG_T("Byte")).c_str())));
            a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("AvailVirtual:%s"), bug_binary_prefix(mem_info.ullAvailPhys, BUG_T("Byte")).c_str())));
            a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("Used-Virtual:%s"), bug_binary_prefix(mem_info.ullTotalVirtual -mem_info.ullAvailPhys, BUG_T("Byte")).c_str())));
            a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("AvailExtendedVirtual:%s"), bug_binary_prefix(mem_info.ullAvailExtendedVirtual, BUG_T("Byte")).c_str())));
        }
        else
        {
            a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("error:%s"), BUG_API_T(bug_get_win32_err_msg)().c_str())));
        }
    }
#endif // 0x0500 <= WINVER
    
    //  [BUG]ドライブ情報のログ出力
    inline void bug_drive_info(bug_logger & a_logger, const bug_char * drive_name, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
    {
        bug_bug_time_scope bug_time_scope(a_current_tick);
        std::basic_string<bug_char> drive_info;

        const bug_char * drive_type = BUG_T("unknown");
        switch(BUG_API_T(GetDriveType)(drive_name))
        {
        case DRIVE_UNKNOWN:     drive_type = BUG_T("unknown");      break;
        case DRIVE_NO_ROOT_DIR: drive_type = BUG_T("no root dir");  break;
        case DRIVE_REMOVABLE:   drive_type = BUG_T("removable");    break;
        case DRIVE_FIXED:       drive_type = BUG_T("fixed");        break;
        case DRIVE_REMOTE:      drive_type = BUG_T("remote");       break;
        case DRIVE_CDROM:       drive_type = BUG_T("cdrom");        break;
        case DRIVE_RAMDISK:     drive_type = BUG_T("ramdisk");      break;
        }
        
        drive_info = BUG_FORM(BUG_T("drive:%c / type:%s"), drive_name[0], drive_type);
        
        bug_char volume_name[MAX_PATH+1];
        bug_char file_system_name[MAX_PATH+1];
        DWORD volume_serial_number;
        DWORD maximum_component_length;
        DWORD file_system_flags;
        BOOL GetVolumeInformation_result =
            BUG_API_T(GetVolumeInformation)
            (
                drive_name,
                volume_name,
                MAX_PATH +1,
                &volume_serial_number,
                &maximum_component_length,
                &file_system_flags,
                file_system_name,
                MAX_PATH +1
            );
        
        if (GetVolumeInformation_result)
        {
            drive_info +=
                BUG_FORM
                (
                    BUG_T(" / label:%s / file-system:%s / serial:0x%08.8X / max-path:%d / flags:0x%08.8X"),
                    volume_name, file_system_name, volume_serial_number, maximum_component_length, file_system_flags
                );
        
            //  GetDiskFreeSpaceEx() はメディアが挿入されていない removable なドライ
            //  ブに対して実行するとGUIでエラーメッセージを表示することがあるので
            //  GetVolumeInformation() が成功した時のみ実行する。
        
            DWORD SectorsPerCluster;
            DWORD BytesPerSector;
            DWORD NumberOfFreeClusters;
            DWORD TotalNumberOfClusters;
            BOOL GetDiskFreeSpace_result =
                BUG_API_T(GetDiskFreeSpace)
                (
                    drive_name,
                    &SectorsPerCluster,
                    &BytesPerSector,
                    &NumberOfFreeClusters,
                    &TotalNumberOfClusters
                );
            if (GetDiskFreeSpace_result)
            {
                drive_info +=
                    BUG_FORM
                    (
                        BUG_T(" / sectors-per-cluster:%d / bytes-per-sector:%dByte"),
                        SectorsPerCluster,
                        BytesPerSector
                    );
            }
            
            ULARGE_INTEGER free_bytes_available;
            ULARGE_INTEGER total_number_of_bytes;
            ULARGE_INTEGER total_number_of_free_bytes;
            BOOL GetDiskFreeSpaceEx_result =
                BUG_API_T(GetDiskFreeSpaceEx)
                (
                    drive_name,
                    &free_bytes_available,
                    &total_number_of_bytes,
                    &total_number_of_free_bytes
                );
            
            if (GetDiskFreeSpaceEx_result)
            {
                drive_info +=
                    BUG_FORM
                    (
                        BUG_T(" / available:%s / total:%s / free:%s"),
                        bug_binary_prefix(free_bytes_available.QuadPart, BUG_T("Byte")).c_str(),
                        bug_binary_prefix(total_number_of_bytes.QuadPart, BUG_T("Byte")).c_str(),
                        bug_binary_prefix(total_number_of_free_bytes.QuadPart, BUG_T("Byte")).c_str()
                    );
            }
        }
        
        a_logger.log_message(BUG_MSG(drive_info.c_str()));
    }
    inline void bug_enum_drive_info(bug_logger & a_logger, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
    {
        bug_bug_time_scope bug_time_scope(a_current_tick);
        bug_scope current_scope(a_logger, BUG_MSG(BUG_T("Drives Information")));
        DWORD drives_mask = GetLogicalDrives();
        bug_char drive_name[8] = BUG_T("A:\\");
        
        while(drives_mask)
        {
            if (drives_mask &0x00000001)
            {
                bug_drive_info(a_logger, drive_name);
            }
            ++(drive_name[0]);
            drives_mask >>= 1;
        }
    }

    //  [BUG]モニター情報のログ出力
#if 0x0500 <= WINVER
    inline BOOL CALLBACK bug_MonitorEnumProc(HMONITOR hMonitor, HDC, LPRECT, LPARAM dwData)
    {
        bug_logger & logger = *(bug_logger *)dwData;
        MONITORINFOEX monitor_info;
        monitor_info.cbSize = sizeof(monitor_info);
        GetMonitorInfo(hMonitor, &monitor_info);
        logger.log_message
        (
            BUG_MSG
            (
                BUG_FORM
                (
                    BUG_T("Monitor Rect:(%d,%d)-(%d,%d) / Work:(%d,%d)-(%d,%d) / Device:%s"),
                    monitor_info.rcMonitor.left, monitor_info.rcMonitor.top, monitor_info.rcMonitor.right, monitor_info.rcMonitor.bottom,
                    monitor_info.rcWork.left, monitor_info.rcWork.top, monitor_info.rcWork.right, monitor_info.rcWork.bottom,
                    monitor_info.szDevice
                )
            )
        );
        return TRUE;
    }
    inline void bug_enum_monitor_info(bug_logger & a_logger, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
    {
        bug_bug_time_scope bug_time_scope(a_current_tick);
        bug_scope current_scope(a_logger, BUG_MSG(BUG_T("Monitor Information")));
        EnumDisplayMonitors(NULL, NULL, bug_MonitorEnumProc, (LPARAM)&a_logger);
    }
#endif // 0x0500 <= WINVER
    
    inline void bug_env(bug_logger & a_logger, const bug_char * env_name, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
    {
        bug_bug_time_scope bug_time_scope(a_current_tick);
        DWORD env_buffer_size = 1024;
        bug_char * env_buffer = new bug_char[env_buffer_size];
        DWORD result = BUG_API_T(GetEnvironmentVariable)(env_name, env_buffer, env_buffer_size);
        if (result)
        {
            if (result <= env_buffer_size)
            {
                delete [] env_buffer;
                env_buffer_size = result +1;
                env_buffer = new bug_char[env_buffer_size];
                BUG_API_T(GetEnvironmentVariable)(env_name, env_buffer, env_buffer_size);
            }
            a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("%s=%s"), env_name, env_buffer)));
        }
        else
        {
            a_logger.log_message(BUG_MSG(BUG_FORM(BUG_T("%s error:%s"), env_name, BUG_API_T(bug_get_win32_err_msg)().c_str())));
        }
        delete [] env_buffer;
    }
    inline void bug_enum_env(bug_logger & a_logger, const bug_char * env_name, ...)
    {
        bug_bug_time_scope bug_time_scope;
        bug_scope current_scope(a_logger, BUG_MSG(BUG_T("Environment Information")));
        bug_env(a_logger, env_name);
        va_list marker;
        va_start(marker, env_name);
        const bug_char * i;
        while(NULL != (i = va_arg(marker, const bug_char *)))
        {
            bug_env(a_logger, i);
        }
        va_end(marker);
    }
    inline void bug_enum_env(bug_logger & a_logger, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
    {
        bug_bug_time_scope bug_time_scope(a_current_tick);
        bug_scope current_scope(a_logger, BUG_MSG(BUG_T("All Environment Information")));
        const bug_char * envs = BUG_API_T(GetEnvironmentStrings)();
        while(*envs)
        {
            a_logger.log_message(BUG_MSG(envs));
            envs += BUG_API_T(lstrlen)(envs) +1;
        }
    }
#if 0x0500 <= WINVER
    //  [BUG]ディスプレイ情報のログ出力
    inline void bug_enum_display_info(bug_logger & a_logger, const bug_profile_time_type & a_current_tick = bug_profile_time_type::get_current_tick())
    {
        bug_bug_time_scope bug_time_scope(a_current_tick);
        bug_scope current_scope(a_logger, BUG_MSG(BUG_T("Display Information")));
        BUG_API_T(DISPLAY_DEVICE) display_device_info;
        display_device_info.cb = sizeof(display_device_info);
        int i = 0;
        while(BUG_API_T(EnumDisplayDevices)(NULL, i++, &display_device_info, 0))
        {
            a_logger.log_message
            (
                BUG_MSG
                (
                    BUG_FORM
                    (
                        BUG_T("Display Name:%s / Context:%s"),
                        display_device_info.DeviceName,
                        display_device_info.DeviceString
                    )
                )
            );
        }
    }
#endif // 0x0500 <= WINVER

#endif // defined(BUG_MS_WINDOWS)

} // namespace bugbeard

template<class target_T>
inline target_T * operator * (bugbeard::bug_new_core & a_new_core, target_T * new_ptr)
{
    a_new_core.close();
    return new_ptr;
}

#if defined(__BORLANDC__) && 0x520 < __BORLANDC__
#   pragma warn .8027
#endif

#if defined(BUG_DEFINE_GLOBAL_LOGGER)
BUG_define_logger(BUG_DEFINE_GLOBAL_LOGGER);
#endif

#if defined(BUG_DEFINE_GLOBAL_PROFILER)
BUG_define_profiler(BUG_DEFINE_GLOBAL_PROFILER);
#endif

#else   //  defined(BUG_LOAD_BUGBEARD)

//
//  vanish macros
//
#   define BUG_MSG(X)           BUG_NOTHING
#   define BUG_LOG              BUG_NOTHING
#   define BUG_VAL(X)           BUG_NOTHING
#   define BUG_FORM
#   define BUG_puts(X)          BUG_NOTHING
#   define BUG_scope(X)         BUG_NOTHING
#   define BUG_scope_with_timelimit(X,timelimit) BUG_NOTHING
#   define BUG_inline_scope(X)  BUG_NOTHING
#   define BUG_inline_scope_with_timelimit(X,timelimit)  BUG_NOTHING
#   define BUG_exec(X)          
#   define BUG_define_logger(X)
#   define BUG_define_profiler(X)

#endif  //  defined(BUG_LOAD_BUGBEARD)


#if defined(_MSC_VER)
#   pragma warning(pop)
#endif


#endif  //  !defined(BUGBEARD_BUG_H)


#if defined(BUG_LOAD_BUGBEARD)

#if defined(BUG_STATEMENT_HACK)
#   define if(X)        if (bugbeard::bug_if_core BUG_ID(bugbeard_if_temporary_object, __LINE__) = bugbeard::bug_if_core(BUG_LOG, BUG_MSG(BUG_T("if (") BUG_T(BUG_MASK_TARGET(#X)) BUG_T(") == ")), X))
#if defined(BUG_NEED_WHILE_CAST)
#   define while(X)     while((bool)bugbeard::bug_while_core(BUG_LOG, BUG_MSG(BUG_T("while (") BUG_T(BUG_MASK_TARGET(#X)) BUG_T(") == ")), X))
#elif defined(BUG_DISABLED_WHILE_SCOPE)
#   define while(X)     while(bugbeard::bug_while_core(BUG_LOG, BUG_MSG(BUG_T("while (") BUG_T(BUG_MASK_TARGET(#X)) BUG_T(") == ")), X))
#else
#   define while(X)     while(bugbeard::bug_while_core BUG_ID(bugbeard_while_temporary_object, __LINE__) = bugbeard::bug_while_core(BUG_LOG, BUG_MSG(BUG_T("while (") BUG_T(BUG_MASK_TARGET(#X)) BUG_T(") == ")), X))
#endif
#if defined(BUG_ENABLED_CPP11_OR_LATER)
#   define switch(X)    switch(auto BUG_ID(bugbeard_switch_temporary_object, __LINE__) = bugbeard::bug_switch_helper(BUG_LOG, BUG_MSG(BUG_T("switch (") BUG_T(BUG_MASK_TARGET(#X)) BUG_T(") == ")), X))
#else
#   if defined(BUG_DISABLED_SWITCH_SCOPE)
#       if defined(BUG_NEED_WHILE_CAST)
#           define switch(X)    switch((int)bugbeard::bug_switch_core(BUG_LOG, BUG_MSG(BUG_T("switch (") BUG_T(BUG_MASK_TARGET(#X)) BUG_T(") == ")), X))
#       else
#           define switch(X)    switch(bugbeard::bug_switch_core(BUG_LOG, BUG_MSG(BUG_T("switch (") BUG_T(BUG_MASK_TARGET(#X)) BUG_T(") == ")), X))
#       endif
#   else
#       if defined(BUG_NEED_WHILE_CAST)
#           define switch(X)    switch((int)bugbeard::bug_switch_core BUG_ID(bugbeard_switch_temporary_object, __LINE__) = bugbeard::bug_switch_core(BUG_LOG, BUG_MSG(BUG_T("switch (") BUG_T(BUG_MASK_TARGET(#X)) BUG_T(") == ")), X))
#       else
#           define switch(X)    switch(bugbeard::bug_switch_core BUG_ID(bugbeard_switch_temporary_object, __LINE__) = bugbeard::bug_switch_core(BUG_LOG, BUG_MSG(BUG_T("switch (") BUG_T(BUG_MASK_TARGET(#X)) BUG_T(") == ")), X))
#       endif
#   endif
#endif
#   define goto         if (BUG_puts(BUG_T("goto"))) assert(false); else goto
#   define break        if (BUG_puts(BUG_T("break"))) break; else break
#   define continue     if (BUG_puts(BUG_T("continue"))) continue; else continue
#if defined(__WATCOMC__)
#   define return       switch(bugbeard::bug_scope_out(BUG_LOG, BUG_MSG(BUG_T("return")))) default: return
#elif defined(BUG_DISABLED_SWITCH_SCOPE)
#   define return       if (bugbeard::bug_scope_out(BUG_LOG, BUG_MSG(BUG_T("return")))) assert(false); else return
#else
#   define return       switch(bugbeard::bug_scope_out(BUG_LOG, BUG_MSG(BUG_T("return")))) default: return
#endif
#   define do           if (bugbeard::bug_scope(BUG_LOG, BUG_MSG(BUG_T("do")))) assert(false); else do
#   define for          if (bugbeard::bug_scope(BUG_LOG, BUG_MSG(BUG_T("for")))) assert(false); else for
#   define try          if (bugbeard::bug_scope(BUG_LOG, BUG_MSG(BUG_T("try")))) assert(false); else try
#if defined(BUG_DISABLED_THROW_SCOPE)
#   define throw        if (BUG_puts(BUG_T("throw"))) assert(false); else throw
#else
#   define throw        if (bugbeard::bug_scope(BUG_LOG, BUG_MSG(BUG_T("throw")))) assert(false); else throw
#endif
#   define new          bugbeard::bug_new_core(BUG_LOG, BUG_MSG(BUG_T("new"))) ?NULL :new
#   define delete       if (bugbeard::bug_scope(BUG_LOG, BUG_MSG(BUG_T("delete")))) assert(false); else delete
#else  //  defined(BUG_STATEMENT_HACK)
#if defined(if)
#undef if
#endif
#if defined(while)
#undef while
#endif
#if defined(switch)
#undef while
#endif
#if defined(goto)
#undef goto
#endif
#if defined(break)
#undef break
#endif
#if defined(continue)
#undef continue
#endif
#if defined(return)
#undef return
#endif
#if defined(do)
#undef do
#endif
#if defined(for)
#undef for
#endif
#if defined(try)
#undef try
#endif
#if defined(throw)
#undef throw
#endif
#if defined(new)
#undef new
#endif
#if defined(delete)
#undef delete
#endif
#endif  //  defined(BUG_STATEMENT_HACK)


///////////////////////////////////////////////////////////////////////////////
//
//  bugbeardを使用することで過剰に発生することになる警告の回避
//

#if defined(_MSC_VER)
#   if _MSC_VER <= 1200
#       pragma warning(disable:4715)
#   endif
#   pragma warning(disable:4065)
#endif

#if  defined(__INTEL_COMPILER)
#   pragma warning(disable:1011)
#endif

#if defined(__BORLANDC__) && 0x520 < __BORLANDC__
#   pragma warn -8027
#endif


#endif  //  defined(BUG_LOAD_BUGBEARD)


/******************************************************************************
    □■□■                  Wraith the Trickster                  □■□■
    ■□■□ ～I'll go with heaven's advantage and fool's wisdom.～ ■□■□
******************************************************************************/
