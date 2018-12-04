# バグベアード -bugbeard-

⚠ この README は編集中です

## about バグベアード -bugbeard-

![バグベアード -bugbeard-](resource/bugbeard48.png)

簡潔かつ乱暴に説明すると、このモジュールは `printf` デバッギングを簡単且つゴージャスに行う為のものです。

バグベアードは C++ プログラマの目となり、その膨大なログで大半のバグを丸裸にします。

- [ライセンス情報](LICENSE_1_0.txt)
- 最終更新日:2011-03-21

> 2008-02-24 "Coming soon..." などと謳いつつ５年近くほったらかしにしてましたが、ついに正式版のリリースです。
> 作者が言うのなんですが、このモジュールは非常に強力且つ凶悪です。ご利用いただければあなたの C++ プログラミングにおけるデバッグシーンに劇的な変化をもたらすであろうことお約束します。

2008-02-25 `inline` 指定が抜けてて複数のコンパイル単位から利用するとリンク時にシンボルが衝突する問題を修正。

2008-03-10 以下の点を修正。

- 悪魔の契約" に「順序不安定」を追記。
- `bug_compact_tree_logger` の追加。
- インクルードの `<sys\timeb.h>` のパスを `<sys/timeb.h>` に修正。
- 命名規則的に明らかにおかしいところ一部修正
  - `BUG_SINT64_TYPE` → `bug_sint64_type`
  - `BUG_UINT64_TYPE` → `bug_uint64_type`
  - `BUG_OutputDebugString_writer` → `bug_OutputDebugString_writer`
  - `BUG_get_winver` → `bug_get_winver`
  - `run_string` → `bug_run_string`
  - `bug_short_clock_stamp_sx_with_date` → `bug_short_clock_stamp_with_date`
- `bug_uni_logger` を削除。( 既にその役目は `bug_thread_local_storage` に取って代わられているので。)

2008-04-01 以下の点を修正。

- `BUG_MASK_SOURCECODE` の追加。
- "悪魔の契約" の「構文の制限」に "例外仕様構文" に関する記述を追記。

2008-06-05 以下の点を修正。

- VC でバグベアード適用時に過剰となる警告を抑止する為に `#pragma warning(disable:1011)` を追加。
- `bug_thread_local_storage::init()` に `base_type::set_target_storage()` を含める。
- g++ のバージョンによってはコンパイルエラーの原因になるので `PTHREAD_MUTEX_INITIALIZER` の使用を中止。( `pthread_mutex_init()` による初期化を行っているので元々不要な指定。 )
- 現時点のバグベアードでは不要だが対称性の観点から bug_unlock クラスを追加。
- ロケーション情報の除去オプション(`BUG_WITHOUT_LOCATION_INFO`)を追加。
- `switch` の値が出力されないバグの解決。

2008-09-23 以下の点を修正。

- プロファイル対応
- カバレッジ対応
- プロファイル＆カバレッジのサンプルコードを追加。
- bug_tsv_logger でヘッダー行を出力するように修正。
- ヘッダー行の出力を抑止する指定マクロ(BUG_WITHOUT_TSV_LOG_HEADER, BUG_WITHOUT_TSV_PROFILE_HEADER, BUG_WITHOUT_TSV_COVERAGE_HEADER)の追加。
- BUG_DISABLED_PSAPI指示マクロの追加( このマクロが定義されると bug_enum_module_version_info() の実装を行わない )。
- QueryPerformance() の結果を秒＋マイクロ秒単位へ変換して表示を行う bug_QueryPerformanceSecond_stamp の追加。
- OSVERSIONINFOEX まわりで WINVER の判定が精確でなかった箇所の修正。
- bug_logger::stamp を private に変更し、bug_logger::get_new_stamp(), bug_logger::get_last_stamp() を追加。
- bug_drive_info() の出力に sectors-per-cluster と bytes-per-sector を追加。
- BUG_DEFINE_GLOBAL_LOGGER と BUG_DEFINE_GLOBAL_PROFILER の追加。
- bug_windows_system_info() の追加。
- bug_file_hash() を追加。
- bug_enum_module_hash() を追加。
- bug_logger::get_instance() の追加および BUG_LOG マクロの修正(ただのリファクタリング)。
- bug_logger::get_process_id() および bug_logger::get_thread_id() をクラスの外に出しに bug_get_process_id() および bug_get_thread_id() に変更(ただのリファクタリング)。
- 不必要な #include &lt;vector&gt; を削除。
- #pragma warning(disable:1011) は VC じゃなくて Intel ででる警告なので icc に限定。

2008-11-01 以下の点を修正。

- プロファイル＆カバレッジ測定サンプル中の bug_tsv_profile_logger を bug_tsv_profiler に訂正。(間違っていたのはこのページ中の表記のみで、ダウンロード用の同サンプルのファイルは元から正しい記述である bug_tsv_profiler になっています。)

2010-02-14 以下の点を修正。

- #include &lt;sys\stat.h&gt; を #include &lt;sys/stat.h&gt; に修正。(<A href="http://twitter.com/graighle/status/6722927223">ご指摘</A>、感謝)
- 一部 BUT_T() が使用されていなかった箇所に BUT_T() を適用。(<A href="http://twitter.com/USAGI_WRP/status/6680888390">ご指摘</A>、感謝)
- bug_get_winver() を Windows 7 などにも対応した最新の状態に更新。
- <A href="http://atnd.org/events/1839">Boost.勉強会</A>で発表した<A href="#primer">バグベアード入門の ustream へのリンクと発表資料</A>の追加。

2011-03-21 ステートメントハックを一度有効化した後、無効化できなくなっていた問題を修正
    
## contents

- <A class="bar" href="#about">about バグベアード -bugbeard-</A>
- <A class="bar" href="#why">why バグベアード？</A>
- <A class="bar" href="#sample">ログ出力サンプル</A>
- <A class="bar" href="#how-to-use">使用方法</A>
- <A class="bar" href="#evil-contract">"悪魔の契約" -EVIL CONTRACT-</A>
- <A class="bar" href="#tutorial">サンプルコード</A>
    - <A class="bar" href="#step1">"Hello, Bugbeard!"</A>
    - <A class="bar" href="#step2">Windows用情報収集サンプル</A>
    - <A class="bar" href="#step3">.tsv形式ログ出力＆マルチスレッドサンプル</A>
    - <A class="bar" href="#step4">バルクログ出力サンプル</A>
    - <A class="bar" href="#step5">プロファイル＆カバレッジ測定サンプル</A>
    - <A class="bar" href="#reference">リファレンス</A>
        - <A class="bar" href="#statements">ステートメントハックによってマクロ置換されるステートメント</A>
        - <A class="bar" href="#macros">マクロ</A>
        - <A class="bar" href="#namespace">名前空間</A>
        - <A class="bar" href="#types">型</A>
        - <A class="bar" href="#functions">関数</A>
        - <A class="bar" href="#profile-columns">プロファイルデータの項目</A>
- <A class="bar" href="#download">ダウンロード</A>
- <A class="bar" href="#primer">バグベアード入門</A>
- <A class="bar" href="#links">links</A>
    
## why バグベアード？

なぜ、ビ○ルダーでもゲイザーでもスズキドゲザエモンでもアスコモイドでもスカイラインでもなくバグベアードなのか？　それはもちろん "不具合"という意味と "盗聴器" という意味を持つ "bug" をその名に含むからです。って、そーじゃなくて、なぜ、デバッガじゃなく良識あるプログラマには一般的に悪しき事とされる printf デバッギング用ロガーであるバグベアドなのか？　ということについて少々説明しておきます。

最初に断っておきますが、「バグベアードがあればデバッガは不要」などと言うつもりもありませんし、情報収集のアスペクトが直交する(※)関係になるのでむしろデバッギングツールとしては相補する関係になると考えます。

> ※ある瞬間のシステム全体の情報...いわば空間に対して強いデバッガと、時間に対して強いバグベアードはその情報収集のアスペクトが直交します。

デバッガにはデバッギングの為のツールとしてはあまり頂けない次のような問題があります。

<DL>
<DT>見ようとしたものしか見えない。</DT>
<DD>
    デバッガによるデバッグでは一般的にプログラマ自身が見ようとした情報しか得られません。プログラマが見ようとした情報の直近であからさまにおかしい挙動があってもプログラマにはそれが伝わらないのです。これでは目隠しされて手探りしているようなものです。
    多くの場合、デバッガを利用してのデバッグではバグの原因を突き止めるに足る決定的なポイントを捕らえる必要があるにも関わらず、そのポイントを捕らえる為の情報はこのような手探りで積み重ねていかねばなりません。
</DD>

<DT>処理の流れを把握しづらい。</DT>
<DD>
    デバッガにはステップ実行や逆実行などの機能もありますが、それでもデバッガでは常にある特定の瞬間のデータしか扱えず、これではなかなか処理の流れを把握できません。
    この為、ステップ実行をやってる最中に明らかにおかしい分岐に入ってもそれがその時に注意を傾けているポイントでなければうっかり見過ごしてしまうのも無理のないことです。
    また、処理の流れが可視化されていない為、デバッガでは正常な場合の処理の流れと異常な場合の処理の流れの比較に困難がつきまといます。
</DD>

<DT>エンドユーザ環境では無力。</DT>
<DD>
    特定のエンドユーザ環境でしか再現しないバグというのは普通によくある話であるにも関わらずデバッガはこの種の再現条件を抱えるバグに対して全く無力です。
</DD>
</DL>


他のも問題はあるでしょうがこれらの問題に対しバグベアードでは次のようになります。

<DL>
<DT>見ようとしたもの以外の情報も見える。</DT>
<DD>
    裏を返せば見たくもないものを見せられたり肝心な情報がその他の情報に埋もれてしまうリスクもあるわけですが、バグベアードでは意識して見ようとした以外の情報も見える為、バグの痕跡を発見しやすくなります。
</DD>

<DT>処理の流れを把握しやすい。</DT>
<DD>
    特にツリー形式のログでは処理の流れを把握しやすく、テキストデータの形になっているので正常の場合の処理の流れと異常な場合の処理の流れの比較も容易です。
</DD>

<DT>エンドユーザ環境でも利用可能。</DT>
<DD>
    エンドユーザにログ上のソースコード断片を見られてしまったり、膨大なログをどうやってエンドユーザに送り返してもらうのかで困ったりすることはあるかもしれませんが、エンドユーザ環境であってもバグベアードは利用できます。
</DD>
</DL>

またバグベアードを利用すればソースコード修正後の動作確認もステップ実行の代わりにただ実行してログを確認するだけで済ませるというお手軽なスタイルを採用することもできます。

バグベアード固有の問題についても以下に挙げておきます。

<DL>
<DT>ログがでかすぎ。</DT>
<DD>
    『とにかくログでかすぎ。時間あたりのログ出力量が動画ファイルを余裕で上回るとかね、もう馬鹿？って感じ。』
    『エンドユーザ環境でも利用可能？こんなでかいログどうやってユーザから送ってもらうのよ？』
    ...とでも言いたくなるようなログ出力量になり、バグベアードを利用してのデバッグはバグの原因を特定する為に必要なほんの数行を見つけ出す為に数十万行のログを追いかけるようなものとなります。
    そのログのサイズは時には数百万行あるいは数千万行以上の非常に膨大なサイズに達することでしょう。
    バグベアードは昨今のPCの強力なパワーがあって初めて実用的なデバッグの手段となり得ます。
</DD>

<DT>ソースコード漏洩</DT>
<DD>
    断片的ではあるのですが相当量のソースコードがログに含まれます。
    エンドユーザ環境などでテストしてもらった際にソースコードが漏洩するリスクを考慮する必要があります。
</DD>

<DT>バグベアードをロードしていると実行形式ファイルが馬鹿でかくなる。</DT>
<DD>
    ログの膨大さに比べれば全然カワイイものですが、バグベアードをロードしていると実行形式ファイルが馬鹿でかくなります。
    大きすぎてメールの添付ファイルで送れなくて困るといったこともあるかもしれません。
</DD>

</DL>

> バグベアードにより出力されたログを追跡してデバッグする際は高速な検索ができるビューア(テキストエディタ)を使用することを強く推奨します。
> バグベアードが出力するログは非常に膨大になりますので検索性能の差が残酷なまでに現れます。
> 例えば、約200MBのログの末尾に現れる文字列を <A href="http://notepad-plus.sourceforge.net/uk/site.htm">Notepad++</A> で検索したところ約 3 分 30 秒もかかってしまいましたが、同じ環境下で<A href="http://sakura-editor.sourceforge.net/" target="_blank">サクラエディタ</A>で検索すれば 2 秒もかかりませんでした。その性能差は実に100倍以上にすら及びます。
    
    
## ログ出力サンプル

```txt
┌──────────────────────────────────────
│日付＆時刻：2008-02-24(日) 23:26:11.874
└─────┬────────────────────────────────
23:26:11.874├┬▽if (1 < current) == true; &lt;tree.cpp&gt;#104
23:26:11.874│├・while (1 < current) == true; &lt;tree.cpp&gt;#109
23:26:11.874│├┬▽if (current %p) == true; &lt;tree.cpp&gt;#111
23:26:11.874││├┬▽if (pn) == false; &lt;tree.cpp&gt;#113
23:26:11.874│││└△if (pn) == false; &lt;tree.cpp&gt;#113
23:26:11.874││├・p(0x00D8FC5C) = 3(0x00000003) &lt;tree.cpp&gt;#126
23:26:11.874││└△if (current %p) == true; &lt;tree.cpp&gt;#111
23:26:11.874│├・while (1 < current) == true; &lt;tree.cpp&gt;#109
23:26:11.874│├┬▽if (current %p) == true; &lt;tree.cpp&gt;#111
23:26:11.874││├┬▽if (pn) == false; &lt;tree.cpp&gt;#113
23:26:11.874│││└△if (pn) == false; &lt;tree.cpp&gt;#113
23:26:11.874││├・p(0x00D8FC5C) = 5(0x00000005) &lt;tree.cpp&gt;#126
23:26:11.874││└△if (current %p) == true; &lt;tree.cpp&gt;#111
23:26:11.874│├・while (1 < current) == true; &lt;tree.cpp&gt;#109
23:26:11.874│├┬▽if (current %p) == true; &lt;tree.cpp&gt;#111
23:26:11.874││├┬▽if (pn) == false; &lt;tree.cpp&gt;#113
23:26:11.874│││└△if (pn) == false; &lt;tree.cpp&gt;#113
```
    
## 使用方法

いくつかのマクロを適宜定義し、bug.h をしかるべき場所で include しコンパイルするだけです。詳細についてはこのページの情報に一通り目を通してください。
    
## "悪魔の契約" -EVIL CONTRACT-

<P>
邪道な技術により構築されたバグベアードは邪悪で忌むべき存在です。
またバグベアードの肝であるステートメントハックにより、さながらナノマシンの如くバグベアードのコードはユーザプログラムを隅々まで侵食します。
故にバグベアードの利用にあたっては以下のような注意が必要となります。

<DL>

<A name="illegal"></A>
<DT>規格違反</DT>
<DD>
    バグベアードは「ステートメントのマクロでの置換」という最上級の規格違反を犯しています。
    これによりバグベアードを利用したプログラムはあらゆる C++ コンパイラでの動作保証は得られなくなります。
    ただし、これはバグベアードの「ステートメントハック」が有効になっている場合の話であり、バグベアードがロードされていない状態を含め「ステートメントハック」が無効になっている場合はその限りではありません。
    そして通常、リリース版のプログラムではバグベアードをロードしないことをオススメします。
</DD>

<A name="stain-error-info"></A>
<DT>エラー情報の侵食</DT>
<DD>
    ユーザプログラムを隅々まで侵食するバグベアードのログ出力コードの影響により、エラー情報(Win32API の GetLastError()で得られるエラーコードやグローバル変数に保持されるC/C++標準ライブラリのエラーコード)が上書きされてしまう可能性があります。
    前項と同様にこれはバグベアードをロードしている状態でのみ発生しうる問題であり、バグベアードをロードしていない状態であればこの問題は発生しません。
</DD>

<A name="restrict-statement"></A>
<DT>構文の制限</DT>
<DD>
    バグベアードのステートメントハックの実装の都合より...
    <DIV class="sample">
    <span class="SpanClass5">if</span>&nbsp;<span class="SpanClass10">(</span><span class="SpanClass16">int</span>&nbsp;<span class="SpanClass11">i</span>&nbsp;<span class="SpanClass10">=</span>&nbsp;<span class="SpanClass11">func</span><span class="SpanClass10">)</span>&nbsp;<span class="SpanClass10">...</span><br/>
    <span class="SpanClass5">switch</span><span class="SpanClass10">(</span><span class="SpanClass16">int</span>&nbsp;<span class="SpanClass11">i</span>&nbsp;<span class="SpanClass10">=</span>&nbsp;<span class="SpanClass11">func</span><span class="SpanClass10">)</span>&nbsp;<span class="SpanClass10">...</span><br/>
    <span class="SpanClass5">while</span><span class="SpanClass10">(</span><span class="SpanClass16">int</span>&nbsp;<span class="SpanClass11">i</span>&nbsp;<span class="SpanClass10">=</span>&nbsp;<span class="SpanClass11">func</span><span class="SpanClass10">)</span>&nbsp;<span class="SpanClass10">...</span><br/>
    </DIV>
    ...のような形でステートメントに属する丸カッコで囲まれた箇所で変数を定義することができません。また...
    <DIV class="sample">
    <span class="SpanClass16">void</span>&nbsp;<span class="SpanClass11">func</span><span class="SpanClass10">(...)</span>&nbsp;<span class="SpanClass5">throw</span><span class="SpanClass10">(...);</span><br/>
    </DIV>
    ...のような例外仕様構文が一切使えません。
    ただし、for ステートメントに関してはこの例外となり for(int i = 0;... などとしても問題ありません。
    また、そもそもステートメントハックを適用しない箇所ではこの制限はありません。
</DD>

<A name="unstable-work"></A>
<DT>動作不安定</DT>
<DD>
    バグベアードはオブジェクトの破棄のタイミングや operator や template 等がコンパイラによって意図通りに適用されるかどうかに強く依存する為、こちらで動作確認を行っていないコンパイラではあまり意図通りに機能することを期待できませんし、動作確認を行っているコンパイラでもバージョンによっては意図通りに機能しないかもしれません。
</DD>

<A name="unstable-log"></A>
<DT>出力ログの変形</DT>
<DD>
    前項と同じく、バグベアードはオブジェクトの破棄のタイミングや operator や template 等がコンパイラによって意図通りに適用されるかどうかに強く依存する為、必ずしもは理想的な形でログを出力できない為に同じソースからコンパイルされたプログラムの出力ログがコンパイラ及びそのバージョンの違いにより変形してしまうことがあります。
    具体的には return ステートメントのログ出力は return fucn(); のような場合、func() 関数の呼び出しが終了した段階で return ステートメントのログを出力するのが理想的ですが、そのような形で実装できない処理系では func(); 関数の呼び出しの前に return ステートメントのログ出力が行われます。
    また別の例では switch ステートメントに対してはスコープ扱いでログを出力するのが理想的ですが、そのように実装できない処理系では switch ステートメントがスコープ扱いされません。
</DD>

<A name="increase-warning"></A>
<DT>過剰な警告(ある意味、真っ当な警告)</DT>
<DD>
    バグベアードをロードしてコンパイルを行うとバグベアードを利用していなければ表示されることはないような警告が過剰に表示されることがあります。
    これは通常、無視して構いません。
    ただし、バグベアードをロードしていない時に表示される警告は通常通りに対処してください。
</DD>

<A name="unstable-sequence"></A>
<DT>順序不安定</DT>
<DD>
    シングルプロセス×シングルスレッドでバグベアードを利用する場合は関係ない話ですが、マルチプロセスもしくはマルチスレッドでバグベアードを利用する場合、複数のプロセス/スレッドの各種処理のログは必ずしもそれらの処理が実行された順番とそのログ出力結果の順番が一致しないことがあります。
    これはログに記録が残る処理が実行されてから実際にそのログ出力が行われるまでに一定時間ではないタイムラグがある為です。
    もちろんこれは異なるプロセス・スレッド間での話であり、同一プロセス・スレッド上の処理が実行された順番とそのログ出力結果の順番は必ず一致します。
</DD>

</DL>

これらを踏まえてなお、悪魔の契約を締結するならばその意思表明として BUG_EVIL_CONTRACT マクロを定義してください。BUG_EVIL_CONTRACT はユーザプログラム全体に非常に強力な影響を及ぼすバグベアードのセーフティを解除する為のマクロです。
契約締結の暁にはバグベアードはさまざまな恩恵と災いをあなたにもたらすでしょう。
</P>

## バグベアードをご利用に当たってのヒント

<DL>
<DT>バグがあった場所のログ出力の為の埋め込みは消さない。</DT>
<DD>
    一度、なんらかのバグ追跡の為に埋め込んだログ出力用コードは基本的には全てソースコード上に残しておくことをオススメします。
    実際にバグがあった箇所の埋め込みについては特に強くオススメします。
    というのもバグというのは一度直したつもりでも修正が十分でなく完全に直ってなかったり、別のバグを埋め込んでしまったりというのもよくある話です。
    また、バグというのは特定箇所に集中する傾向もあります。
    この為、その時目的としていたバグの直しが完了した後も、バグ追跡の為に埋め込んだログ出力用コードは全てソースコード上に残しておくことをオススメします。
    ログ出力量が過剰になってしまう場合は条件ディレクティブを使って必要な時以外は無効にしておくのがよいでしょう。
</DD>

<DT>三項演算子のかわりに if を使用する。</DT>
<DD>
    通常であればむしろ三項演算子が適用できる場面であれば if の使用を控えるといったことが推奨されるかもしれませんが、あえて if を使用することで、バグベアード(のステートメントハック)で条件の判定結果を簡単にログに残せます。
</DD>

<DT>明記が不要な場合でも return を記述する。</DT>
<DD>
    戻り型が void の関数やコンストラクタ、デストラクタでも return を記述しておくとその分ログ出力が増え、バグ追跡に役立ちます。
</DD>

<DT>フィルタ機能を利用する。</DT>
<DD>
    マルチプロセス及びマルチスレッドによるログ出力を同じファイル等に対して行うと、特に tree 形式でのログ出力は追跡中のログが他のプロセス及び他のスレッドによる出力とごちゃ混ぜになって追跡し辛くなることがありますが、その場合は適宜そのログの表示に使ってるエディタもしくはビューアが有するフィルタ機能を使い、プロセスIDやスレッドIDで表示を絞り込むとよいでしょう。
</DD>

<DT>デバッグ以外での利用。</DT>
<DD>
    バグベアードには環境および処理系にあまり依存せずに使えるスマートポインタ、スレッドローカルストレージ、ミューテックス等々さまざま機能を内包していますのでちょっとしたプログラムでそれらの機能を利用するのもよいでしょう。
</DD>

<DT>Excel を *.tsv ログのビューアとして使用する場合は Excel2007 以降で。</DT>
<DD>
    Excel2003 以前では 65,536 行までしか扱えない為、極小規模なプログラムのログならどうにかなるかもしれませんが、かなり厳しいです。
    Excel2007 以降であれば、1,048,576行まで扱えます。
    ...それでもプログラムによっては全然足りないでしょうが。
</DD>
</DL>


## サンプルコード

- <A class="bar" href="#step1">"Hello, Bugbeard!"</A>
- <A class="bar" href="#step2">Windows用情報収集サンプル</A>
- <A class="bar" href="#step3">.tsv形式ログ出力＆マルチスレッドサンプル</A>
- <A class="bar" href="#step4">バルクログ出力サンプル</A>
- <A class="bar" href="#step5">プロファイル＆カバレッジ測定サンプル</A>
            
<A name="step1"></A>
### "Hello, Bugbeard!"

#### サンプルコード

```c++
/******************************************************************************
    バグベアード -bugbeard-
        サンプル "simple.cpp" ソースファイル
                                            Coded by Wraith in Feb 18, 2007.
*****************************************************************************/


///////////////////////////////////////////////////////////////////////////////
//
//  includes
//

#include <stdio.h>
#include <stdlib.h>


///////////////////////////////////////////////////////////////////////////////
//
//  [BUG]bugbeard
//

#if defined(NDEBUG)
#define BUG_DISABLE_BUGBEARD    //  リリース版ではバグベアードをロードしない
#endif

#define BUG_EVIL_CONTRACT       //  "悪魔の契約"
#include "bug.h"                //  ロガーを定義する為にステートメントハックを有効にしない状態で include

//  標準エラーにツリー形式の出力を行うロガーの定義
BUG_define_logger(new bugbeard::bug_tree_logger(new bugbeard::bug_file_writer_base(stderr)));

#define BUG_STATEMENT_HACK      //  ステートメントハックの設定
#include "bug.h"                //  ステートメントハックを有効にする為、再度 include


///////////////////////////////////////////////////////////////////////////////
//
//  user codes
//

int main(int argc, char args[])
{
    argc, args;                 //  警告除け

    //  [BUG]固定メッセージをログ出力
    BUG_puts("Hello, Bugbeard!");
    
    //  [BUG]コンパイル情報のログ出力
    BUG_exec(bugbeard::bug_compile_info(BUG_LOG));

    //  [BUG]コマンドライン引数のログ出力
    BUG_exec(bugbeard::bug_arg_info(BUG_LOG, argc, args));
    
    //  [BUG]変数をログ出力
    BUG_puts(BUG_VAL(args[0]));
    
    //  [BUG]書式付ログ出力
    BUG_puts(BUG_FORM("このプログラムのファイル名："%s"", args[0]));
    
    return EXIT_SUCCESS;
}


/******************************************************************************
    □■□■                  Wraith the Trickster                  □■□■
    ■□■□ ～I'll go with heaven's advantage and fool's wisdom.～ ■□■□
******************************************************************************/
```

#### 出力結果(標準エラー)

```txt
┌──────────────────────────────────────
│日付＆時刻：2008-02-24(日) 18:06:13.739
└─────┬────────────────────────────────
18:06:13.743├・Hello, Bugbeard! &lt;sample/simple.cpp&gt;#46
18:06:13.744├┬▽Compile Information &lt;bug.h&gt;#2839
18:06:13.745│├・Compiler:Borland C++(0x0564) &lt;bug.h&gt;#2841
18:06:13.745│├・Compile Date:Feb 24 2008 / Compile Time:18:06:11 &lt;bug.h&gt;#2843
18:06:13.746│└△Compile Information &lt;bug.h&gt;#2839
18:06:13.747├┬▽Commandline Argument Information &lt;bug.h&gt;#2849
18:06:13.748│├・argc(0x0012F994) = 1(0x00000001) &lt;bug.h&gt;#2850
18:06:13.749│├・args[0]:o:\cxx\bugbeard\simple.exe &lt;bug.h&gt;#2853
18:06:13.750│└△Commandline Argument Information &lt;bug.h&gt;#2849
18:06:13.751├・args[0](0x00DE21C4) = "o:\cxx\bugbeard\simple.exe" &lt;sample/simple.cpp&gt;#55
18:06:13.752├・このプログラムのファイル名："o:\cxx\bugbeard\simple.exe" &lt;sample/simple.cpp&gt;#58
18:06:13.753├・return &lt;sample/simple.cpp&gt;#60
┌─────┴────────────────────────────────
│日付＆時刻：2008-02-24(日) 18:06:13.754
└──────────────────────────────────────
```

#### 解説

このサンプルでの一番の肝は...

<DIV class="sample">
<span class="SpanClass2">///////////////////////////////////////////////////////////////////////////////<br/>
//<br/>
//&nbsp;&nbsp;[BUG]bugbeard<br/>
//<br/>
</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#if&nbsp;defined(NDEBUG)<br/>
#define&nbsp;BUG_DISABLE_BUGBEARD&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;リリース版ではバグベアードをロードしない<br/>
</span><span class="SpanClass9">#endif<br/>
</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#define&nbsp;BUG_EVIL_CONTRACT&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;"悪魔の契約"<br/>
</span><span class="SpanClass9">#include&nbsp;"bug.h"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;ロガーを定義する為にステートメントハックを有効にしない状態で include<br/>
</span><span class="SpanClass0"><br/>
</span><span class="SpanClass2">//&nbsp;&nbsp;標準エラーにツリー形式の出力を行うロガーの定義<br/>
</span><span class="SpanClass11">BUG_define_logger</span><span class="SpanClass10">(</span><span class="SpanClass5">new</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_tree_logger</span><span class="SpanClass10">(</span><span class="SpanClass5">new</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_file_writer_base</span><span class="SpanClass10">(</span><span class="SpanClass11">stderr</span><span class="SpanClass10">)));</span><span class="SpanClass0"><br/>
<br/>
</span><span class="SpanClass9">#define&nbsp;BUG_STATEMENT_HACK&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;ステートメントハックの設定<br/>
</span><span class="SpanClass9">#include&nbsp;"bug.h"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;ステートメントハックを有効にする為、再度 include<br/>
</span>
</DIV>

...この部分ですが、まぁ、最初は所謂 "おまじない" の類だとでも思ってください。

BUG_define_logger() の行によりログの出力形式等を指定しています。

NDEBUG マクロが定義された場合の assert() マクロと同様に、BUG_DISABLE_BUGBEARD マクロが定義されると BUG_* な命名になっているコードは全て消え去ります。

なお、Windowsではデフォルトで標準エラーがアスキーモードになっている為、改行コード "\r\n" が無駄に拡張され "\r\r\n" になってしまうので標準エラーをファイルへリダイレクトすると不格好になります。Windowsでは bugbeard::bug_file_writer で直接ファイルに出力するか、bugbeard::bug_OutputDebugString_writer で OutputDebugString() で出力することを推奨します。

<A name="step2"></A>
### Windows用情報収集サンプル

#### サンプルコード

<DIV class="sample">
<span class="SpanClass3">/******************************************************************************<br/>
&nbsp;&nbsp;&nbsp;&nbsp;バグベアード&nbsp;-bugbeard-<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;サンプル&nbsp;"win.cpp"&nbsp;ソースファイル<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Coded&nbsp;by&nbsp;Wraith&nbsp;in&nbsp;Feb&nbsp;18,&nbsp;2007.<br/>
******************************************************************************/</span><span class="SpanClass0"><br/>
<br/>
<br/>
</span><span class="SpanClass2">///////////////////////////////////////////////////////////////////////////////<br/>
//<br/>
//&nbsp;&nbsp;includes<br/>
//<br/>
</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#include&nbsp;&lt;stdio.h&gt;<br/>
#include&nbsp;&lt;stdlib.h&gt;<br/>
</span><span class="SpanClass0"><br/>
<br/>
</span><span class="SpanClass2">///////////////////////////////////////////////////////////////////////////////<br/>
//<br/>
//&nbsp;&nbsp;[BUG]bugbeard<br/>
//<br/>
</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#if&nbsp;defined(NDEBUG)<br/>
#define&nbsp;BUG_DISABLE_BUGBEARD&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;リリース版ではバグベアードをロードしない<br/>
</span><span class="SpanClass9">#endif<br/>
</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#define&nbsp;BUG_EVIL_CONTRACT&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;"悪魔の契約"<br/>
</span><span class="SpanClass9">#include&nbsp;"bug.h"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;ロガーを定義する為にステートメントハックを有効にしない状態で include<br/>
</span><span class="SpanClass0"><br/>
</span><span class="SpanClass2">//&nbsp;&nbsp;OutputDebugString()&nbsp;でツリー形式の出力を行うロガーの定義<br/>
</span><span class="SpanClass11">BUG_define_logger</span><span class="SpanClass10">(</span><span class="SpanClass5">new</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_tree_logger</span><span class="SpanClass10">(</span><span class="SpanClass5">new</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_OutputDebugString_writer</span><span class="SpanClass10">()));</span><span class="SpanClass0"><br/>
<br/>
</span><span class="SpanClass9">#define&nbsp;BUG_STATEMENT_HACK&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;ステートメントハックの設定<br/>
</span><span class="SpanClass9">#include&nbsp;"bug.h"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;ステートメントハックを有効にする為、再度 include<br/>
</span><span class="SpanClass0"><br/>
<br/>
</span><span class="SpanClass2">///////////////////////////////////////////////////////////////////////////////<br/>
//<br/>
//&nbsp;&nbsp;user&nbsp;codes<br/>
//<br/>
</span><span class="SpanClass0"><br/>
</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">main</span><span class="SpanClass10">(</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">argc</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass16">char</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">*</span><span class="SpanClass11">args</span><span class="SpanClass10">[])</span><span class="SpanClass0"><br/>
</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">argc</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">args</span><span class="SpanClass10">;</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;警告除け<br/>
</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">puts</span><span class="SpanClass10">(</span><span class="SpanClass6">"このサンプルでは Win32API の OutputDebugString() でログを出力しています。"</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">puts</span><span class="SpanClass10">(</span><span class="SpanClass6">"ご利用のIDEのデバッグ出力表示機能や <A href="http://technet.microsoft.com/en-us/sysinternals/bb896647.aspx" target="_blank">sysinternals の DebugView</A> などで出力内容を確認できます。"</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;<br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]コンパイル情報のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_exec</span><span class="SpanClass10">(</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_compile_info</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_LOG</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
<br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]コマンドライン引数のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_exec</span><span class="SpanClass10">(</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_arg_info</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_LOG</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">argc</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">args</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;<br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]Windowsバージョン情報のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_exec</span><span class="SpanClass10">(</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_windows_version_info</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_LOG</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;<br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]Windowsシステム情報のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_exec</span><span class="SpanClass10">(</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_windows_system_info</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_LOG</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;<br/>
</span><span class="SpanClass9">#if&nbsp;0x0500&nbsp;&lt;=&nbsp;WINVER<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;各種モジュールバージョン情報のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_exec</span><span class="SpanClass10">(</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_enum_module_version_info</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_LOG</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#endif<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;<br/>
</span><span class="SpanClass9">#if&nbsp;0x0500&nbsp;&lt;=&nbsp;WINVER<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;各種モジュールハッシュ値のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_exec</span><span class="SpanClass10">(</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_enum_module_hash</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_LOG</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#endif<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;<br/>
</span><span class="SpanClass9">#if&nbsp;0x0500&nbsp;&lt;=&nbsp;WINVER<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]メモリ情報のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_exec</span><span class="SpanClass10">(</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_memory_info</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_LOG</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#endif<br/>
</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]ドライブ情報のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_exec</span><span class="SpanClass10">(</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_enum_drive_info</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_LOG</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
<br/>
</span><span class="SpanClass9">#if&nbsp;0x0500&nbsp;&lt;=&nbsp;WINVER<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]モニター情報のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_exec</span><span class="SpanClass10">(</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_enum_monitor_info</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_LOG</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]ディスプレイ情報のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_exec</span><span class="SpanClass10">(</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_enum_display_info</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_LOG</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#endif<br/>
</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG](全ての)環境変数情報のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_exec</span><span class="SpanClass10">(</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_enum_env</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_LOG</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;<br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">return</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">EXIT_SUCCESS</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
<br/>
<br/>
</span><span class="SpanClass3">/******************************************************************************<br/>
&nbsp;&nbsp;&nbsp;&nbsp;□■□■&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Wraith&nbsp;the&nbsp;Trickster&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;□■□■<br/>
&nbsp;&nbsp;&nbsp;&nbsp;■□■□&nbsp;～I'll&nbsp;go&nbsp;with&nbsp;heaven's&nbsp;advantage&nbsp;and&nbsp;fool's&nbsp;wisdom.～&nbsp;■□■□<br/>
******************************************************************************/</span><span class="SpanClass0"><br/>
</span>
</DIV>

#### 出力結果(標準出力)

<DIV class="sample">
<PRE>
このサンプルでは Win32API の OutputDebugString() でログを出力しています。
ご利用のIDEのデバッグ出力表示機能や <A href="http://technet.microsoft.com/en-us/sysinternals/bb896647.aspx" target="_blank">sysinternals の DebugView</A> などで出力内容を確認できます。
</PRE>
</DIV>

#### 出力結果(OutputDebugString())

> ※意図的に一部編集してます。

<DIV class="sample">
<PRE>
┌────────────────────────────────────── 
│日付＆時刻：2008-09-23(火) 22:06:59.771 
└─────┬──────────────────────────────── 
22:06:59.772├┬▽Compile Information <bug.h>#4450 
22:06:59.772│├・Compiler:Borland C++(0x0564) <bug.h>#4452 
22:06:59.772│├・Compile Date:Sep 23 2008 / Compile Time:22:06:25 <bug.h>#4454 
22:06:59.772│└△Compile Information <bug.h>#4450 
22:06:59.772├┬▽Commandline Argument Information <bug.h>#4461 
22:06:59.772│├・argc(0x0012D500) = 1(0x00000001) <bug.h>#4462 
22:06:59.772│├・args[0]:O:\cxx\bugbeard\work\win.exe <bug.h>#4465 
22:06:59.772│└△Commandline Argument Information <bug.h>#4461 
22:06:59.773├┬▽Windows Version Information <bug.h>#4505 
22:06:59.773│├・Microsoft Windows Vista Business Edition, 32-bit <bug.h>#4508 
22:06:59.773│├・OSVERSIONINFO dwMajorVersion:6 / dwMinorVersion:0 / dwBuildNumber:6001 / dwPlatformId:2 / szCSDVersion:Service Pack 1 <bug.h>#4510 
22:06:59.773│├・OSVERSIONINFOEX wServicePackMajor:1 / wServicePackMinor:0 / wSuiteMask:256 / wProductType:1 / wReserved:30 <bug.h>#4514 
22:06:59.773│└△Windows Version Information <bug.h>#4505 
22:06:59.773├┬▽Windows System Information <bug.h>#4474 
22:06:59.773│├・wProcessorArchitecture:0 <bug.h>#4488 
22:06:59.773│├・wReserved:0 <bug.h>#4489 
22:06:59.773│├・dwPageSize:4096 <bug.h>#4490 
22:06:59.773│├・lpMinimumApplicationAddress:00010000 <bug.h>#4491 
22:06:59.773│├・lpMaximumApplicationAddress:7FFEFFFF <bug.h>#4492 
22:06:59.773│├・dwActiveProcessorMask:3 <bug.h>#4493 
22:06:59.773│├・dwNumberOfProcessors:2 <bug.h>#4494 
22:06:59.773│├・dwProcessorType:586 <bug.h>#4495 
22:06:59.773│├・dwAllocationGranularity:65536 <bug.h>#4496 
22:06:59.773│├・wProcessorLevel:6 <bug.h>#4497 
22:06:59.773│├・wProcessorRevision:3846 <bug.h>#4498 
22:06:59.773│└△Windows System Information <bug.h>#4474 
22:06:59.773├┬▽Module Version Information <bug.h>#4591 
22:06:59.773│├・module:"O:\cxx\bugbeard\work\win.exe" / no version information <bug.h>#4584 
22:06:59.773│├・module:"C:\Windows\system32\ntdll.dll" / language:041104b0 / FileDescription: NT レイヤ DLL / FileVersion: 6.0.6001.18000 (longhorn_rtm.080118-1840) / ProductName: MicrosoftR WindowsR Operating System / ProductVersion: 6.0.6001.18000 / CompanyName: Microsoft Corporation / OriginalFilename: ntdll.dll.mui <bug.h>#4577 
22:06:59.774│├・module:"C:\Windows\system32\kernel32.dll" / language:041104b0 / FileDescription: Windows NT ベース API クライアント DLL / FileVersion: 6.0.6001.18000 (longhorn_rtm.080118-1840) / ProductName: MicrosoftR WindowsR Operating System / ProductVersion: 6.0.6001.18000 / CompanyName: Microsoft Corporation / OriginalFilename: kernel32 <bug.h>#4577 
22:06:59.774│├・module:"C:\Windows\system32\ADVAPI32.DLL" / language:041104b0 / FileDescription: Advanced Windows 32 ベース API / FileVersion: 6.0.6001.18000 (longhorn_rtm.080118-1840) / ProductName: MicrosoftR WindowsR Operating System / ProductVersion: 6.0.6001.18000 / CompanyName: Microsoft Corporation / OriginalFilename: advapi32.dll.mui <bug.h>#4577 
22:06:59.774│├・module:"C:\Windows\system32\RPCRT4.dll" / language:041104b0 / FileDescription: リモート プロシージャ コール ランタイム / FileVersion: 6.0.6001.18000 (longhorn_rtm.080118-1840) / ProductName: MicrosoftR WindowsR Operating System / ProductVersion: 6.0.6001.18000 / CompanyName: Microsoft Corporation / OriginalFilename: rpcrt4.dll.mui <bug.h>#4577 
22:06:59.774│├・module:"C:\Windows\system32\VERSION.DLL" / language:040904b0 / FileDescription: Version Checking and File Installation Libraries / FileVersion: 6.0.6001.18000 (longhorn_rtm.080118-1840) / ProductName: MicrosoftR WindowsR Operating System / ProductVersion: 6.0.6001.18000 / CompanyName: Microsoft Corporation / OriginalFilename: VERSION.DLL <bug.h>#4577 
22:06:59.774│├・module:"C:\Windows\system32\msvcrt.dll" / language:040904b0 / FileDescription: Windows NT CRT DLL / FileVersion: 7.0.6001.18000 (longhorn_rtm.080118-1840) / ProductName: MicrosoftR WindowsR Operating System / ProductVersion: 7.0.6001.18000 / CompanyName: Microsoft Corporation / OriginalFilename: msvcrt.dll <bug.h>#4577 
22:06:59.775│├・module:"C:\Windows\system32\USER32.DLL" / language:041104b0 / FileDescription: マルチユーザー Windows ユーザー API クライアント DLL / FileVersion: 6.0.6001.18000 (longhorn_rtm.080118-1840) / ProductName: MicrosoftR WindowsR Operating System / ProductVersion: 6.0.6001.18000 / CompanyName: Microsoft Corporation / OriginalFilename: user32 <bug.h>#4577 
22:06:59.775│├・module:"C:\Windows\system32\GDI32.dll" / language:040904b0 / FileDescription: GDI Client DLL / FileVersion: 6.0.6001.18023 (vistasp1_gdr.080221-1537) / ProductName: MicrosoftR WindowsR Operating System / ProductVersion: 6.0.6001.18023 / CompanyName: Microsoft Corporation / OriginalFilename: gdi32 <bug.h>#4577 
22:06:59.775│├・module:"C:\Windows\system32\PSAPI.DLL" / language:040904b0 / FileDescription: Process Status Helper / FileVersion: 6.0.6000.16386 (vista_rtm.061101-2205) / ProductName: MicrosoftR WindowsR Operating System / ProductVersion: 6.0.6000.16386 / CompanyName: Microsoft Corporation / OriginalFilename: PSAPI <bug.h>#4577 
22:06:59.775│├・module:"C:\Windows\system32\IMM32.DLL" / language:040904b0 / FileDescription: Multi-User Windows IMM32 API Client DLL / FileVersion: 6.0.6001.18000 (longhorn_rtm.080118-1840) / ProductName: MicrosoftR WindowsR Operating System / ProductVersion: 6.0.6001.18000 / CompanyName: Microsoft Corporation / OriginalFilename: imm32 <bug.h>#4577 
22:06:59.775│├・module:"C:\Windows\system32\MSCTF.dll" / language:041104b0 / FileDescription: MSCTF サーバー DLL / FileVersion: 6.0.6000.16386 (vista_rtm.061101-2205) / ProductName: MicrosoftR WindowsR Operating System / ProductVersion: 6.0.6000.16386 / CompanyName: Microsoft Corporation / OriginalFilename: MSCTF.DLL.MUI <bug.h>#4577 
22:06:59.776│├・module:"C:\Windows\system32\LPK.DLL" / language:040904b0 / FileDescription: Language Pack / FileVersion: 6.0.6001.18000 (longhorn_rtm.080118-1840) / ProductName: MicrosoftR WindowsR Operating System / ProductVersion: 6.0.6001.18000 / CompanyName: Microsoft Corporation / OriginalFilename: LanguagePack <bug.h>#4577 
22:06:59.776│├・module:"C:\Windows\system32\USP10.dll" / language:040904b0 / FileDescription: Uniscribe Unicode script processor / FileVersion: 1.0626.6001.18000 (longhorn_rtm.080118-1840) / ProductName: Microsoft(R) Uniscribe Unicode script processor / ProductVersion: 1.0626.6001.18000 / CompanyName: Microsoft Corporation / OriginalFilename: Uniscribe <bug.h>#4577 
22:06:59.776│└△Module Version Information <bug.h>#4591 
22:06:59.776├┬▽Module Hash <bug.h>#4605 
22:06:59.789│├・file:"O:\cxx\bugbeard\work\win.exe" / hash(MD5):DA0A29DA42E371316446BFE64A528921 <bug.h>#4528 
22:06:59.792│├・file:"C:\Windows\system32\ntdll.dll" / hash(MD5):172E1B9EB61167AD232291A6761501BF <bug.h>#4528 
22:06:59.796│├・file:"C:\Windows\system32\kernel32.dll" / hash(MD5):DC2338093F91BA4E0512208E60206DDD <bug.h>#4528 
22:06:59.799│├・file:"C:\Windows\system32\ADVAPI32.DLL" / hash(MD5):C44A1766E93E506EE2102A305799E1A1 <bug.h>#4528 
22:06:59.802│├・file:"C:\Windows\system32\RPCRT4.dll" / hash(MD5):520CE99A9C1A3B14078BB39272424652 <bug.h>#4528 
22:06:59.802│├・file:"C:\Windows\system32\VERSION.DLL" / hash(MD5):187D588F7A1A45DE48B8540401A90850 <bug.h>#4528 
22:06:59.805│├・file:"C:\Windows\system32\msvcrt.dll" / hash(MD5):04CBEAA089B6A752B3EB660BEE8C4964 <bug.h>#4528 
22:06:59.808│├・file:"C:\Windows\system32\USER32.DLL" / hash(MD5):B974D9F06DC7D1908E825DC201681269 <bug.h>#4528 
22:06:59.809│├・file:"C:\Windows\system32\GDI32.dll" / hash(MD5):F77456EB036D834BFBC700EB2414879E <bug.h>#4528 
22:06:59.810│├・file:"C:\Windows\system32\PSAPI.DLL" / hash(MD5):93A1732F7F997E36A5C3893539E2FF02 <bug.h>#4528 
22:06:59.811│├・file:"C:\Windows\system32\IMM32.DLL" / hash(MD5):EC17194A193CD8E90D27CFB93DFA9A2E <bug.h>#4528 
22:06:59.814│├・file:"C:\Windows\system32\MSCTF.dll" / hash(MD5):030981927E732FD4013910B3B06BD45B <bug.h>#4528 
22:06:59.815│├・file:"C:\Windows\system32\LPK.DLL" / hash(MD5):DD496299B7351E16E602FC4299345A33 <bug.h>#4528 
22:06:59.817│├・file:"C:\Windows\system32\USP10.dll" / hash(MD5):3122DAF86B33ED8AC4662D07593025D7 <bug.h>#4528 
22:06:59.817│└△Module Hash <bug.h>#4605 
22:06:59.817├┬▽Memory Information <bug.h>#4623 
22:06:59.817│├・load:61% <bug.h>#4628 
22:06:59.817│├・TotalPhys:2.98GiByte(3201634304) <bug.h>#4629 
22:06:59.817│├・AvailPhys:1.14GiByte(1222332416) <bug.h>#4630 
22:06:59.817│├・Used-Phys:1.84GiByte(1979301888) <bug.h>#4631 
22:06:59.817│├・TotalPageFile:6.16GiByte(6611963904) <bug.h>#4632 
22:06:59.817│├・AvailPageFile:1.14GiByte(1222332416) <bug.h>#4633 
22:06:59.817│├・Used-PageFile:5.02GiByte(5389631488) <bug.h>#4634 
22:06:59.817│├・TotalVirtual:2.00GiByte(2147352576) <bug.h>#4635 
22:06:59.817│├・AvailVirtual:1.14GiByte(1222332416) <bug.h>#4636 
22:06:59.817│├・Used-Virtual:882MiByte(925020160) <bug.h>#4637 
22:06:59.817│├・AvailExtendedVirtual:0Byte(0) <bug.h>#4638 
22:06:59.817│└△Memory Information <bug.h>#4623 
22:06:59.817├┬▽Drives Information <bug.h>#4752 
22:06:59.817│├・drive:C / type:fixed / label:***** / file-system:NTFS / serial:0x******** / max-path:255 / flags:0x002700FF / sectors-per-cluster:8 / bytes-per-sector:512Byte / available:6.08GiByte(6528913408) / total:74.5GiByte(80003198976) / free:6.08GiByte(6528913408) <bug.h>#4747 
22:06:59.818│├・drive:D / type:fixed / label:** / file-system:NTFS / serial:0x******** / max-path:255 / flags:0x002700FF / sectors-per-cluster:8 / bytes-per-sector:512Byte / available:39.0GiByte(41832468480) / total:74.5GiByte(80007262208) / free:39.0GiByte(41832468480) <bug.h>#4747 
22:06:59.818│├・drive:F / type:fixed / label:*** / file-system:NTFS / serial:0x******** / max-path:255 / flags:0x002700FF / sectors-per-cluster:8 / bytes-per-sector:512Byte / available:726GiByte(779961614336) / total:931GiByte(1000202240000) / free:726GiByte(779961614336) <bug.h>#4747 
22:06:59.819│├・drive:G / type:cdrom <bug.h>#4747 
22:06:59.831│├・drive:I / type:removable <bug.h>#4747 
22:06:59.842│├・drive:J / type:removable <bug.h>#4747 
22:06:59.854│├・drive:K / type:removable <bug.h>#4747 
22:06:59.866│├・drive:L / type:removable <bug.h>#4747 
22:06:59.866│├・drive:O / type:fixed / label:**** / file-system:NTFS / serial:0x******** / max-path:255 / flags:0x002700FF / sectors-per-cluster:8 / bytes-per-sector:512Byte / available:10.4GiByte(11172679680) / total:114GiByte(122683387904) / free:10.4GiByte(11172679680) <bug.h>#4747 
22:06:59.866│├・drive:X / type:fixed / label:***** / file-system:NTFS / serial:0x******** / max-path:255 / flags:0x002700FF / sectors-per-cluster:8 / bytes-per-sector:512Byte / available:143GiByte(154588205056) / total:202GiByte(217409646592) / free:143GiByte(154588205056) <bug.h>#4747 
22:06:59.866│└△Drives Information <bug.h>#4752 
22:06:59.866├┬▽Monitor Information <bug.h>#4793 
22:06:59.866│├・Monitor Rect:(0,0)-(1920,1200) / Work:(0,0)-(1920,1200) / Device:\\.\DISPLAY1 <bug.h>#4786 
22:06:59.866│├・Monitor Rect:(1920,176)-(3200,1200) / Work:(1920,176)-(3200,1200) / Device:\\.\DISPLAY2 <bug.h>#4786 
22:06:59.866│└△Monitor Information <bug.h>#4793 
22:06:59.866├┬▽Display Information <bug.h>#4851 
22:06:59.866│├・Display Name:\\.\DISPLAY1 / Context:NVIDIA GeForce 8600 GTS <bug.h>#4867 
22:06:59.867│├・Display Name:\\.\DISPLAY2 / Context:NVIDIA GeForce 8600 GTS <bug.h>#4867 
22:06:59.867│├・Display Name:\\.\DISPLAYV1 / Context:RDPDD Chained DD <bug.h>#4867 
22:06:59.867│├・Display Name:\\.\DISPLAYV2 / Context:RDP Encoder Mirror Driver <bug.h>#4867 
22:06:59.867│└△Display Information <bug.h>#4851 
22:06:59.867├┬▽All Environment Information <bug.h>#4838 
22:06:59.867│├・=::=::\ <bug.h>#4842 
22:06:59.867│├・=C:=C:\Users\wraith <bug.h>#4842 
22:06:59.867│├・=ExitCode=00000000 <bug.h>#4842 
22:06:59.867│├・=O:=O:\cxx\bugbeard\work <bug.h>#4842 
22:06:59.867│├・ALLUSERSPROFILE=C:\ProgramData <bug.h>#4842 
22:06:59.867│├・APPDATA=C:\Users\wraith\AppData\Roaming <bug.h>#4842 
22:06:59.867│├・BDSCOMMONDIR=C:\Users\Public\Documents\RAD Studio\5.0 <bug.h>#4842 
22:06:59.867│├・CLASSPATH=.;C:\Program Files\Java\jre1.5.0_10\lib\ext\QTJava.zip <bug.h>#4842 
22:06:59.867│├・CommonProgramFiles=C:\Program Files\Common Files <bug.h>#4842 
22:06:59.867│├・COMPUTERNAME=CRUISER <bug.h>#4842 
22:06:59.867│├・ComSpec=C:\Windows\system32\cmd.exe <bug.h>#4842 
22:06:59.867│├・FP_NO_HOST_CHECK=NO <bug.h>#4842 
22:06:59.867│├・HOMEDRIVE=C: <bug.h>#4842 
22:06:59.867│├・HOMEPATH=\Users\wraith <bug.h>#4842 
22:06:59.867│├・LOCALAPPDATA=C:\Users\wraith\AppData\Local <bug.h>#4842 
22:06:59.867│├・LOGONSERVER=\\CRUISER <bug.h>#4842 
22:06:59.867│├・NUMBER_OF_PROCESSORS=2 <bug.h>#4842 
22:06:59.867│├・OS=Windows_NT <bug.h>#4842 
22:06:59.867│├・Path=************************************************************************************************************************* <bug.h>#4842 
22:06:59.867│├・PATHEXT=**************************************************** <bug.h>#4842 
22:06:59.867│├・PROCESSOR_ARCHITECTURE=x86 <bug.h>#4842 
22:06:59.867│├・PROCESSOR_IDENTIFIER=x86 Family 6 Model 15 Stepping 6, GenuineIntel <bug.h>#4842 
22:06:59.868│├・PROCESSOR_LEVEL=6 <bug.h>#4842 
22:06:59.868│├・PROCESSOR_REVISION=**** <bug.h>#4842 
22:06:59.868│├・ProgramData=C:\ProgramData <bug.h>#4842 
22:06:59.868│├・ProgramFiles=C:\Program Files <bug.h>#4842 
22:06:59.868│├・PROMPT=$P$G <bug.h>#4842 
22:06:59.868│├・PUBLIC=C:\Users\Public <bug.h>#4842 
22:06:59.868│├・QTJAVA=C:\Program Files\Java\jre1.5.0_10\lib\ext\QTJava.zip <bug.h>#4842 
22:06:59.868│├・SESSIONNAME=Console <bug.h>#4842 
22:06:59.868│├・solomoncmd="O:\solomon\bcc32" win.cpp  <bug.h>#4842 
22:06:59.868│├・SystemDrive=C: <bug.h>#4842 
22:06:59.868│├・SystemRoot=C:\Windows <bug.h>#4842 
22:06:59.868│├・TEMP=C:\Users\wraith\AppData\Local\Temp <bug.h>#4842 
22:06:59.868│├・TMP=C:\Users\wraith\AppData\Local\Temp <bug.h>#4842 
22:06:59.868│├・UGII_3DCONNEXION_LIBRARY=%UGII_BASE_DIR%\ugalliance\vendor\startup\3DxNX.dll <bug.h>#4842 
22:06:59.868│├・USERDOMAIN=cruiser <bug.h>#4842 
22:06:59.868│├・USERNAME=wraith <bug.h>#4842 
22:06:59.868│├・USERPROFILE=C:\Users\wraith <bug.h>#4842 
22:06:59.868│├・windir=C:\Windows <bug.h>#4842 
22:06:59.868│└△All Environment Information <bug.h>#4838 
22:06:59.868├・return <win.cpp>#88 
┌─────┴──────────────────────────────── 
│日付＆時刻：2008-09-23(火) 22:06:59.868 
└────────────────────────────────────── 
</PRE>
</DIV>

#### 解説

<DIV class="sample">
<span class="SpanClass2">//&nbsp;&nbsp;OutputDebugString()&nbsp;でツリー形式の出力を行うロガーの定義<br/>
</span><span class="SpanClass11">BUG_define_logger</span><span class="SpanClass10">(</span><span class="SpanClass5">new</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_tree_logger</span><span class="SpanClass10">(</span><span class="SpanClass5">new</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_OutputDebugString_writer</span><span class="SpanClass10">()));</span><span class="SpanClass0"><br/>
</DIV>
        ...この指定により標準エラーへの出力ではなく OutputDebugString() を使ってのログ出力を行っています。
        <A href="http://technet.microsoft.com/en-us/sysinternals/bb896647.aspx" target="_blank">DebugView</A> などでログ出力を確認できます。
        上のようなログ出力結果は一見、過剰に思えるかもしれませんが、バグベアードによって出力されるログは一般的に非常に膨大なものになり、この程度ハッキリ言って誤差の範囲ですから Windows でバグベアードを利用される場合...
<DIV class="sample">
<span class="SpanClass0">
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]コンパイル情報のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_exec</span><span class="SpanClass10">(</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_compile_info</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_LOG</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
<br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]コマンドライン引数のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_exec</span><span class="SpanClass10">(</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_arg_info</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_LOG</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">argc</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">args</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;<br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]Windowsバージョン情報のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_exec</span><span class="SpanClass10">(</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_windows_version_info</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_LOG</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;<br/>
</span><span class="SpanClass9">#if&nbsp;0x0500&nbsp;&lt;=&nbsp;WINVER<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;各種モジュールバージョン情報のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_exec</span><span class="SpanClass10">(</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_enum_module_version_info</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_LOG</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#endif<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;<br/>
</span><span class="SpanClass9">#if&nbsp;0x0500&nbsp;&lt;=&nbsp;WINVER<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]メモリ情報のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_exec</span><span class="SpanClass10">(</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_memory_info</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_LOG</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#endif<br/>
</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]ドライブ情報のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_exec</span><span class="SpanClass10">(</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_enum_drive_info</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_LOG</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
<br/>
</span><span class="SpanClass9">#if&nbsp;0x0500&nbsp;&lt;=&nbsp;WINVER<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]モニター情報のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_exec</span><span class="SpanClass10">(</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_enum_monitor_info</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_LOG</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]ディスプレイ情報のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_exec</span><span class="SpanClass10">(</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_enum_display_info</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_LOG</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#endif<br/>
</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG](全ての)環境変数情報のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_exec</span><span class="SpanClass10">(</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_enum_env</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_LOG</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
</span>
</DIV>
        ...この部分のコードを丸々コピペして利用されることを強く推奨いたします。

<A name="step3"></A>
### .tsv形式ログ出力＆マルチスレッドサンプル
#### サンプルコード
<DIV class="sample">
<span class="SpanClass3">/******************************************************************************<br/>
&nbsp;&nbsp;&nbsp;&nbsp;バグベアード&nbsp;-bugbeard-<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;サンプル&nbsp;"tsv.cpp"&nbsp;ソースファイル<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Coded&nbsp;by&nbsp;Wraith&nbsp;in&nbsp;Feb&nbsp;18,&nbsp;2007.<br/>
******************************************************************************/</span><span class="SpanClass0"><br/>
<br/>
<br/>
</span><span class="SpanClass2">///////////////////////////////////////////////////////////////////////////////<br/>
//<br/>
//&nbsp;&nbsp;includes<br/>
//<br/>
</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#include&nbsp;&lt;stdio.h&gt;<br/>
#include&nbsp;&lt;stdlib.h&gt;<br/>
#if&nbsp;defined(__GNUC__)<br/>
#&nbsp;&nbsp;&nbsp;include&nbsp;&lt;pthread.h&gt;<br/>
#else<br/>
#&nbsp;&nbsp;&nbsp;include&nbsp;&lt;process.h&gt;<br/>
#endif<br/>
</span><span class="SpanClass0"><br/>
<br/>
</span><span class="SpanClass2">///////////////////////////////////////////////////////////////////////////////<br/>
//<br/>
//&nbsp;&nbsp;[BUG]bugbeard<br/>
//<br/>
</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#if&nbsp;defined(NDEBUG)<br/>
#define&nbsp;BUG_DISABLE_BUGBEARD&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;リリース版ではバグベアードをロードしない<br/>
</span><span class="SpanClass9">#endif<br/>
</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#define&nbsp;BUG_EVIL_CONTRACT&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;"悪魔の契約"<br/>
</span><span class="SpanClass9">#define&nbsp;BUG_MULTI_THREAD&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;マルチスレッドモデルでバグベアードを利用<br/>
</span><span class="SpanClass9">#include&nbsp;"bug.h"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;ロガーを定義する為にステートメントハックを有効にしない状態で include<br/>
</span><span class="SpanClass0"><br/>
</span><span class="SpanClass2">//&nbsp;&nbsp;共用ライターの定義<br/>
</span><span class="SpanClass11">BUG_exec</span><span class="SpanClass10">(</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_smart_writer</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">common_writer</span><span class="SpanClass10">(</span><span class="SpanClass5">new</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_file_writer_base</span><span class="SpanClass10">(</span><span class="SpanClass11">stderr</span><span class="SpanClass10">)));</span><span class="SpanClass0"><br/>
<br/>
</span><span class="SpanClass2">//&nbsp;&nbsp;標準エラーにTSV形式の出力を行うロガーの定義(メインスレッド用)<br/>
</span><span class="SpanClass11">BUG_define_logger</span><span class="SpanClass10">(</span><span class="SpanClass5">new</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_tsv_logger</span><span class="SpanClass10">(</span><span class="SpanClass11">common_writer</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
<br/>
</span><span class="SpanClass9">#define&nbsp;BUG_STATEMENT_HACK&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;ステートメントハックの設定<br/>
</span><span class="SpanClass9">#include&nbsp;"bug.h"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;ステートメントハックを有効にする為、再度 include<br/>
</span><span class="SpanClass0"><br/>
<br/>
</span><span class="SpanClass2">///////////////////////////////////////////////////////////////////////////////<br/>
//<br/>
//&nbsp;&nbsp;user&nbsp;codes<br/>
//<br/>
</span><span class="SpanClass0"><br/>
</span><span class="SpanClass2">//<br/>
//&nbsp;&nbsp;thread<br/>
//<br/>
</span><span class="SpanClass9">#if&nbsp;defined(BUG_MS_WINDOWS)<br/>
#define&nbsp;BUG_THREAD_RESULT&nbsp;DWORD<br/>
#define&nbsp;BUG_THREAD_CALL&nbsp;__stdcall<br/>
#define&nbsp;BUG_THREAD_HANDLE&nbsp;HANDLE<br/>
#else<br/>
#define&nbsp;BUG_THREAD_RESULT&nbsp;void&nbsp;*<br/>
#define&nbsp;BUG_THREAD_CALL<br/>
#define&nbsp;BUG_THREAD_HANDLE&nbsp;pthread_t<br/>
#endif<br/>
</span><span class="SpanClass0"><br/>
</span><span class="SpanClass2">//&nbsp;&nbsp;スレッドの開始<br/>
</span><span class="SpanClass11">BUG_THREAD_HANDLE</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">open_thread</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_THREAD_RESULT</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_THREAD_CALL</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">*</span><span class="SpanClass11">func</span><span class="SpanClass10">)(</span><span class="SpanClass16">void</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">*),</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass16">void</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">*</span><span class="SpanClass11">data</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#if&nbsp;defined(BUG_MS_WINDOWS)<br/>
#&nbsp;&nbsp;&nbsp;if&nbsp;defined(__BORLANDC__)&nbsp;||&nbsp;defined(__INTEL_COMPILER)&nbsp;||&nbsp;defined(_MSC_VER)<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">DWORD</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">thread_id</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">return</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">(</span><span class="SpanClass11">HANDLE</span><span class="SpanClass10">)</span><span class="SpanClass11">_beginthreadex</span><span class="SpanClass10">(</span><span class="SpanClass5">NULL</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass4">0</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">(</span><span class="SpanClass16">unsigned</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">(</span><span class="SpanClass11">__stdcall</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">*)(</span><span class="SpanClass16">void</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">*))</span><span class="SpanClass11">func</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">data</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass4">0</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">(</span><span class="SpanClass16">unsigned</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">*)&</span><span class="SpanClass11">thread_id</span><span class="SpanClass10">);</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br/>
</span><span class="SpanClass9">#&nbsp;&nbsp;&nbsp;else<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">return</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">CreateThread</span><span class="SpanClass10">(</span><span class="SpanClass5">NULL</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass4">4096</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">func</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">data</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass4">0</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass5">NULL</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#&nbsp;&nbsp;&nbsp;endif<br/>
#else<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_THREAD_HANDLE</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">handle</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">pthread_create</span><span class="SpanClass10">(&</span><span class="SpanClass11">handle</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass5">NULL</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">func</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">data</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">return</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">handle</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#endif<br/>
</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
<br/>
</span><span class="SpanClass2">//&nbsp;&nbsp;スレッド終了まで待機<br/>
</span><span class="SpanClass16">void</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">wait_and_close_thread</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_THREAD_HANDLE</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">handle</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#if&nbsp;defined(BUG_MS_WINDOWS)<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">WaitForSingleObject</span><span class="SpanClass10">(</span><span class="SpanClass11">handle</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">INFINITE</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">CloseHandle</span><span class="SpanClass10">(</span><span class="SpanClass11">handle</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#else<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">pthread_join</span><span class="SpanClass10">(</span><span class="SpanClass11">handle</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass5">NULL</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#endif<br/>
</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
<br/>
<br/>
</span><span class="SpanClass2">//<br/>
//&nbsp;&nbsp;素因数分解<br/>
//<br/>
</span><span class="SpanClass9">#if&nbsp;defined(_MSC_VER)&nbsp;&&&nbsp;1300&nbsp;&lt;&nbsp;_MSC_VER<br/>
#&nbsp;&nbsp;&nbsp;pragma&nbsp;warning(disable:4996)<br/>
#endif<br/>
</span><span class="SpanClass16">void</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">factorize</span><span class="SpanClass10">(</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">number</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass16">char</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">buffer</span><span class="SpanClass10">[</span><span class="SpanClass4">256</span><span class="SpanClass10">];</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass16">char</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">*</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">anchor</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">buffer</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">anchor</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">+=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">sprintf</span><span class="SpanClass10">(</span><span class="SpanClass11">anchor</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass6">"%d&nbsp;=&nbsp;"</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">number</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">current</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">number</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">if</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">(</span><span class="SpanClass4">1</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">&lt;</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">current</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">p</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass4">2</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">pn</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass4">0</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">inc</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass4">1</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">while</span><span class="SpanClass10">(</span><span class="SpanClass4">1</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">&lt;</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">current</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">if</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">(</span><span class="SpanClass11">current</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">%</span><span class="SpanClass11">p</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">if</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">(</span><span class="SpanClass11">pn</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">anchor</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">+=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">sprintf</span><span class="SpanClass10">(</span><span class="SpanClass11">anchor</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass6">"%d"</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">p</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">if</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">(</span><span class="SpanClass4">1</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">&lt;</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">pn</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">anchor</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">+=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">sprintf</span><span class="SpanClass10">(</span><span class="SpanClass11">anchor</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass6">"^%d"</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">pn</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">anchor</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">+=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">sprintf</span><span class="SpanClass10">(</span><span class="SpanClass11">anchor</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass6">"&nbsp;*&nbsp;"</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">pn</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass4">0</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">p</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">+=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">inc</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]値のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_puts</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_VAL</span><span class="SpanClass10">(</span><span class="SpanClass11">p</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">inc</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass4">2</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">else</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">current</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">/=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">p</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]値のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_puts</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_VAL</span><span class="SpanClass10">(</span><span class="SpanClass11">current</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">++</span><span class="SpanClass11">pn</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]値のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_puts</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_VAL</span><span class="SpanClass10">(</span><span class="SpanClass11">pn</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">anchor</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">+=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">sprintf</span><span class="SpanClass10">(</span><span class="SpanClass11">anchor</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass6">"%d"</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">p</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">if</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">(</span><span class="SpanClass4">1</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">&lt;</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">pn</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">anchor</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">+=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">sprintf</span><span class="SpanClass10">(</span><span class="SpanClass11">anchor</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass6">"^%d"</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">pn</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">else</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">anchor</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">+=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">sprintf</span><span class="SpanClass10">(</span><span class="SpanClass11">anchor</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass6">"%d"</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">current</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">puts</span><span class="SpanClass10">(</span><span class="SpanClass11">buffer</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">return</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
</span><span class="SpanClass11">BUG_THREAD_RESULT</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">BUG_THREAD_CALL</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">factorize_thread</span><span class="SpanClass10">(</span><span class="SpanClass16">void</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">*</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">data</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]スレッドローカルロガーの定義<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_define_logger</span><span class="SpanClass10">(</span><span class="SpanClass5">new</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_tsv_logger</span><span class="SpanClass10">(</span><span class="SpanClass11">common_writer</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">factorize</span><span class="SpanClass10">((</span><span class="SpanClass16">int</span><span class="SpanClass10">)</span><span class="SpanClass11">data</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">return</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass4">0</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
<br/>
<br/>
</span><span class="SpanClass2">//<br/>
//&nbsp;&nbsp;スタートアップ<br/>
//<br/>
</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">main</span><span class="SpanClass10">(</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">argc</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass16">char</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">*</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">args</span><span class="SpanClass10">[])</span><span class="SpanClass0"><br/>
</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]コンパイル情報のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_exec</span><span class="SpanClass10">(</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_compile_info</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_LOG</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
<br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]コマンドライン引数のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_exec</span><span class="SpanClass10">(</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_arg_info</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_LOG</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">argc</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">args</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
<br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_THREAD_HANDLE</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">*</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">thread_list</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass5">new</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">BUG_THREAD_HANDLE</span><span class="SpanClass10">[</span><span class="SpanClass11">argc</span><span class="SpanClass10">];</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;<br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;スレッド起動<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">for</span><span class="SpanClass10">(</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">i</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass4">1</span><span class="SpanClass10">;</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">i</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">&lt;</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">argc</span><span class="SpanClass10">;</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">++</span><span class="SpanClass11">i</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">thread_list</span><span class="SpanClass10">[</span><span class="SpanClass11">i</span><span class="SpanClass10">]</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">open_thread</span><span class="SpanClass10">(</span><span class="SpanClass11">factorize_thread</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">(</span><span class="SpanClass16">void</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">*)</span><span class="SpanClass11">atoi</span><span class="SpanClass10">(</span><span class="SpanClass11">args</span><span class="SpanClass10">[</span><span class="SpanClass11">i</span><span class="SpanClass10">]));</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;スレッド待機<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">for</span><span class="SpanClass10">(</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">i</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass4">1</span><span class="SpanClass10">;</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">i</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">&lt;</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">argc</span><span class="SpanClass10">;</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">++</span><span class="SpanClass11">i</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">wait_and_close_thread</span><span class="SpanClass10">(</span><span class="SpanClass11">thread_list</span><span class="SpanClass10">[</span><span class="SpanClass11">i</span><span class="SpanClass10">]);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;<br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">delete</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">[]</span><span class="SpanClass11">thread_list</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;<br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">return</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">EXIT_SUCCESS</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
<br/>
<br/>
</span><span class="SpanClass3">/******************************************************************************<br/>
&nbsp;&nbsp;&nbsp;&nbsp;□■□■&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Wraith&nbsp;the&nbsp;Trickster&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;□■□■<br/>
&nbsp;&nbsp;&nbsp;&nbsp;■□■□&nbsp;～I'll&nbsp;go&nbsp;with&nbsp;heaven's&nbsp;advantage&nbsp;and&nbsp;fool's&nbsp;wisdom.～&nbsp;■□■□<br/>
******************************************************************************/</span><span class="SpanClass0"><br/>
</span>
</DIV>

#### 出力結果(標準出力)

```txt
101 = 101
301 = 7 * 43
201 = 3 * 67
```

#### 出力結果(標準エラー)

<DIV class="sample">
<PRE>
20:04:19.182	540	0	bug.h	2462	▽bugbeard session root
20:04:19.183	540	1	bug.h	2463	日付＆時刻：2008-02-24(日) 20:04:19.183
20:04:19.183	540	1	bug.h	2839	▽Compile Information
20:04:19.183	540	2	bug.h	2841	Compiler:Visual C++(1400)
20:04:19.183	540	2	bug.h	2843	Compile Date:Feb 24 2008 / Compile Time:20:02:37
20:04:19.183	540	2	bug.h	2839	△Compile Information
20:04:19.183	540	1	bug.h	2849	▽Commandline Argument Information
20:04:19.183	540	2	bug.h	2850	argc(0x0012FAC8) = 4(0x00000004)
20:04:19.183	540	2	bug.h	2853	args[0]:tsv
20:04:19.183	540	2	bug.h	2853	args[1]:101
20:04:19.183	540	2	bug.h	2853	args[2]:201
20:04:19.183	540	2	bug.h	2853	args[3]:301
20:04:19.183	540	2	bug.h	2849	△Commandline Argument Information
20:04:19.183	540	1	tsv.cpp	176	▽new
20:04:19.183	540	2	tsv.cpp	176	△new
20:04:19.183	540	1	tsv.cpp	179	▽for
20:04:19.183	540	2	tsv.cpp	69	return
20:04:19.183	5772	0	bug.h	2462	▽bugbeard session root
20:04:19.183	540	2	tsv.cpp	69	return
20:04:19.183	5772	1	bug.h	2463	日付＆時刻：2008-02-24(日) 20:04:19.183
20:04:19.183	5772	1	tsv.cpp	104	▽if (1 &lt; current) == true;
20:04:19.183	540	2	tsv.cpp	69	return
20:04:19.183	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.183	540	2	tsv.cpp	179	△for
20:04:19.183	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.183	540	1	tsv.cpp	184	▽for
20:04:19.183	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.183	868	0	bug.h	2462	▽bugbeard session root
20:04:19.183	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.183	868	1	bug.h	2463	日付＆時刻：2008-02-24(日) 20:04:19.183
20:04:19.183	5772	3	tsv.cpp	126	p(0x0133FC5C) = 3(0x00000003)
20:04:19.183	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.183	868	1	tsv.cpp	104	▽if (1 &lt; current) == true;
20:04:19.183	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.183	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.183	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.183	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.183	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.183	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.183	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.183	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.183	5772	3	tsv.cpp	126	p(0x0133FC5C) = 5(0x00000005)
20:04:19.183	868	3	tsv.cpp	126	p(0x0143FC5C) = 3(0x00000003)
20:04:19.183	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.183	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.183	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.183	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.183	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.183	868	2	tsv.cpp	111	▽if (current %p) == false;
20:04:19.183	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.183	868	3	tsv.cpp	135	current(0x0143FD9C) = 67(0x00000043)
20:04:19.183	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.183	868	3	tsv.cpp	140	pn(0x0143FC54) = 1(0x00000001)
20:04:19.183	5772	3	tsv.cpp	126	p(0x0133FC5C) = 7(0x00000007)
20:04:19.183	868	3	tsv.cpp	111	△if (current %p) == false;
20:04:19.184	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.184	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.184	4264	0	bug.h	2462	▽bugbeard session root
20:04:19.184	868	3	tsv.cpp	113	▽if (pn) == true;
20:04:19.184	4264	1	bug.h	2463	日付＆時刻：2008-02-24(日) 20:04:19.184
20:04:19.184	868	4	tsv.cpp	116	▽if (1 &lt; pn) == false;
20:04:19.184	4264	1	tsv.cpp	104	▽if (1 &lt; current) == true;
20:04:19.184	868	5	tsv.cpp	116	△if (1 &lt; pn) == false;
20:04:19.184	4264	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.184	868	4	tsv.cpp	113	△if (pn) == true;
20:04:19.184	4264	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.183	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.184	4264	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.184	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.184	4264	4	tsv.cpp	113	△if (pn) == false;
20:04:19.184	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.184	4264	3	tsv.cpp	126	p(0x0153FC5C) = 3(0x00000003)
20:04:19.184	4264	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.184	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.184	4264	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.184	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.184	4264	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.184	5772	3	tsv.cpp	126	p(0x0133FC5C) = 9(0x00000009)
20:04:19.184	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.184	4264	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.184	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.184	4264	4	tsv.cpp	113	△if (pn) == false;
20:04:19.184	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.184	4264	3	tsv.cpp	126	p(0x0153FC5C) = 5(0x00000005)
20:04:19.184	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.184	4264	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.184	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.184	4264	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.184	5772	3	tsv.cpp	126	p(0x0133FC5C) = 11(0x0000000B)
20:04:19.184	4264	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.184	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.184	4264	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.184	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.184	4264	4	tsv.cpp	113	△if (pn) == false;
20:04:19.184	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.184	4264	3	tsv.cpp	126	p(0x0153FC5C) = 7(0x00000007)
20:04:19.184	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.184	4264	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.184	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.184	4264	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.184	5772	3	tsv.cpp	126	p(0x0133FC5C) = 13(0x0000000D)
20:04:19.184	4264	2	tsv.cpp	111	▽if (current %p) == false;
20:04:19.184	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.184	4264	3	tsv.cpp	135	current(0x0153FD9C) = 43(0x0000002B)
20:04:19.184	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.184	4264	3	tsv.cpp	140	pn(0x0153FC54) = 1(0x00000001)
20:04:19.184	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.184	4264	3	tsv.cpp	111	△if (current %p) == false;
20:04:19.184	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.184	4264	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.184	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.184	4264	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.184	5772	3	tsv.cpp	126	p(0x0133FC5C) = 15(0x0000000F)
20:04:19.184	4264	3	tsv.cpp	113	▽if (pn) == true;
20:04:19.184	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.184	4264	4	tsv.cpp	116	▽if (1 &lt; pn) == false;
20:04:19.184	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.184	4264	5	tsv.cpp	116	△if (1 &lt; pn) == false;
20:04:19.184	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.184	4264	4	tsv.cpp	113	△if (pn) == true;
20:04:19.184	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.184	4264	3	tsv.cpp	126	p(0x0153FC5C) = 9(0x00000009)
20:04:19.184	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.184	4264	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.184	5772	3	tsv.cpp	126	p(0x0133FC5C) = 17(0x00000011)
20:04:19.184	4264	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.184	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.184	4264	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.184	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.184	4264	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.184	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.184	4264	4	tsv.cpp	113	△if (pn) == false;
20:04:19.184	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.184	4264	3	tsv.cpp	126	p(0x0153FC5C) = 11(0x0000000B)
20:04:19.184	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.184	4264	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.184	5772	3	tsv.cpp	126	p(0x0133FC5C) = 19(0x00000013)
20:04:19.184	4264	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.184	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.184	4264	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.184	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.184	4264	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.184	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.184	4264	4	tsv.cpp	113	△if (pn) == false;
20:04:19.185	4264	3	tsv.cpp	126	p(0x0153FC5C) = 13(0x0000000D)
20:04:19.184	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.185	4264	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.185	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.185	4264	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.185	5772	3	tsv.cpp	126	p(0x0133FC5C) = 21(0x00000015)
20:04:19.185	4264	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.185	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.185	4264	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.185	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.185	4264	4	tsv.cpp	113	△if (pn) == false;
20:04:19.185	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.185	4264	3	tsv.cpp	126	p(0x0153FC5C) = 15(0x0000000F)
20:04:19.185	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.185	4264	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.185	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.185	4264	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.185	5772	3	tsv.cpp	126	p(0x0133FC5C) = 23(0x00000017)
20:04:19.185	4264	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.185	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.185	4264	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.185	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.185	4264	4	tsv.cpp	113	△if (pn) == false;
20:04:19.185	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.185	4264	3	tsv.cpp	126	p(0x0153FC5C) = 17(0x00000011)
20:04:19.185	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.185	4264	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.185	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.185	4264	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.185	5772	3	tsv.cpp	126	p(0x0133FC5C) = 25(0x00000019)
20:04:19.185	4264	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.185	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.185	4264	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.185	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.185	4264	4	tsv.cpp	113	△if (pn) == false;
20:04:19.185	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.185	4264	3	tsv.cpp	126	p(0x0153FC5C) = 19(0x00000013)
20:04:19.185	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.185	4264	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.185	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.185	4264	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.185	5772	3	tsv.cpp	126	p(0x0133FC5C) = 27(0x0000001B)
20:04:19.185	4264	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.185	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.185	4264	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.185	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.185	4264	4	tsv.cpp	113	△if (pn) == false;
20:04:19.185	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.185	4264	3	tsv.cpp	126	p(0x0153FC5C) = 21(0x00000015)
20:04:19.185	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.185	4264	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.185	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.185	4264	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.185	5772	3	tsv.cpp	126	p(0x0133FC5C) = 29(0x0000001D)
20:04:19.185	4264	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.185	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.185	4264	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.185	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.185	4264	4	tsv.cpp	113	△if (pn) == false;
20:04:19.185	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.185	4264	3	tsv.cpp	126	p(0x0153FC5C) = 23(0x00000017)
20:04:19.185	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.185	4264	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.185	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.185	4264	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.185	5772	3	tsv.cpp	126	p(0x0133FC5C) = 31(0x0000001F)
20:04:19.185	4264	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.185	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.185	4264	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.185	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.185	4264	4	tsv.cpp	113	△if (pn) == false;
20:04:19.185	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.185	4264	3	tsv.cpp	126	p(0x0153FC5C) = 25(0x00000019)
20:04:19.185	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.185	4264	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.185	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.185	4264	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.185	5772	3	tsv.cpp	126	p(0x0133FC5C) = 33(0x00000021)
20:04:19.185	4264	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.185	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.185	4264	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.185	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.185	4264	4	tsv.cpp	113	△if (pn) == false;
20:04:19.185	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.185	4264	3	tsv.cpp	126	p(0x0153FC5C) = 27(0x0000001B)
20:04:19.185	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.185	4264	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.185	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.185	4264	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.185	5772	3	tsv.cpp	126	p(0x0133FC5C) = 35(0x00000023)
20:04:19.185	4264	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.185	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.185	4264	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.185	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.185	4264	4	tsv.cpp	113	△if (pn) == false;
20:04:19.185	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.185	4264	3	tsv.cpp	126	p(0x0153FC5C) = 29(0x0000001D)
20:04:19.185	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.185	4264	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.185	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.185	4264	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.185	5772	3	tsv.cpp	126	p(0x0133FC5C) = 37(0x00000025)
20:04:19.185	4264	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.185	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.185	4264	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.185	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.184	868	3	tsv.cpp	126	p(0x0143FC5C) = 5(0x00000005)
20:04:19.185	4264	4	tsv.cpp	113	△if (pn) == false;
20:04:19.186	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.186	4264	3	tsv.cpp	126	p(0x0153FC5C) = 31(0x0000001F)
20:04:19.186	4264	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.186	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.186	4264	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.186	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.186	4264	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.186	5772	3	tsv.cpp	126	p(0x0133FC5C) = 39(0x00000027)
20:04:19.186	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.186	4264	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.186	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.186	4264	4	tsv.cpp	113	△if (pn) == false;
20:04:19.186	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.186	4264	3	tsv.cpp	126	p(0x0153FC5C) = 33(0x00000021)
20:04:19.186	4264	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.186	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.186	4264	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.186	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.186	4264	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.186	5772	3	tsv.cpp	126	p(0x0133FC5C) = 41(0x00000029)
20:04:19.186	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.186	4264	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.186	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.186	4264	4	tsv.cpp	113	△if (pn) == false;
20:04:19.186	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.186	4264	3	tsv.cpp	126	p(0x0153FC5C) = 35(0x00000023)
20:04:19.186	4264	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.186	4264	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.186	4264	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.186	4264	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.186	4264	4	tsv.cpp	113	△if (pn) == false;
20:04:19.186	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.186	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.186	5772	3	tsv.cpp	126	p(0x0133FC5C) = 43(0x0000002B)
20:04:19.186	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.186	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.186	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.186	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.186	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.186	5772	3	tsv.cpp	126	p(0x0133FC5C) = 45(0x0000002D)
20:04:19.186	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.186	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.186	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.186	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.186	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.186	5772	3	tsv.cpp	126	p(0x0133FC5C) = 47(0x0000002F)
20:04:19.186	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.186	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.186	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.186	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.186	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.186	5772	3	tsv.cpp	126	p(0x0133FC5C) = 49(0x00000031)
20:04:19.186	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.186	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.186	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.186	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.186	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.186	5772	3	tsv.cpp	126	p(0x0133FC5C) = 51(0x00000033)
20:04:19.186	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.186	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.186	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.186	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.186	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.186	5772	3	tsv.cpp	126	p(0x0133FC5C) = 53(0x00000035)
20:04:19.186	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.186	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.186	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.186	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.186	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.187	5772	3	tsv.cpp	126	p(0x0133FC5C) = 55(0x00000037)
20:04:19.187	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.187	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.187	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.187	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.187	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.187	5772	3	tsv.cpp	126	p(0x0133FC5C) = 57(0x00000039)
20:04:19.187	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.187	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.187	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.187	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.187	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.187	5772	3	tsv.cpp	126	p(0x0133FC5C) = 59(0x0000003B)
20:04:19.187	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.187	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.187	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.187	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.187	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.187	5772	3	tsv.cpp	126	p(0x0133FC5C) = 61(0x0000003D)
20:04:19.187	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.187	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.187	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.187	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.187	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.187	5772	3	tsv.cpp	126	p(0x0133FC5C) = 63(0x0000003F)
20:04:19.187	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.187	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.187	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.187	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.187	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.187	5772	3	tsv.cpp	126	p(0x0133FC5C) = 65(0x00000041)
20:04:19.187	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.187	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.187	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.187	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.187	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.187	5772	3	tsv.cpp	126	p(0x0133FC5C) = 67(0x00000043)
20:04:19.187	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.187	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.187	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.187	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.187	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.187	5772	3	tsv.cpp	126	p(0x0133FC5C) = 69(0x00000045)
20:04:19.187	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.187	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.187	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.187	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.187	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.187	5772	3	tsv.cpp	126	p(0x0133FC5C) = 71(0x00000047)
20:04:19.187	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.187	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.187	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.187	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.187	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.187	5772	3	tsv.cpp	126	p(0x0133FC5C) = 73(0x00000049)
20:04:19.187	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.187	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.187	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.187	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.188	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.188	5772	3	tsv.cpp	126	p(0x0133FC5C) = 75(0x0000004B)
20:04:19.188	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.188	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.188	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.188	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.188	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.188	5772	3	tsv.cpp	126	p(0x0133FC5C) = 77(0x0000004D)
20:04:19.188	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.188	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.188	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.188	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.188	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.188	5772	3	tsv.cpp	126	p(0x0133FC5C) = 79(0x0000004F)
20:04:19.188	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.188	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.188	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.188	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.188	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.188	5772	3	tsv.cpp	126	p(0x0133FC5C) = 81(0x00000051)
20:04:19.188	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.188	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.188	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.188	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.188	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.188	5772	3	tsv.cpp	126	p(0x0133FC5C) = 83(0x00000053)
20:04:19.188	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.188	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.188	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.188	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.188	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.188	5772	3	tsv.cpp	126	p(0x0133FC5C) = 85(0x00000055)
20:04:19.188	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.188	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.188	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.188	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.188	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.188	5772	3	tsv.cpp	126	p(0x0133FC5C) = 87(0x00000057)
20:04:19.188	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.188	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.188	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.188	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.188	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.188	5772	3	tsv.cpp	126	p(0x0133FC5C) = 89(0x00000059)
20:04:19.188	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.188	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.188	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.188	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.188	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.188	5772	3	tsv.cpp	126	p(0x0133FC5C) = 91(0x0000005B)
20:04:19.188	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.188	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.188	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.188	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.188	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.188	5772	3	tsv.cpp	126	p(0x0133FC5C) = 93(0x0000005D)
20:04:19.188	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.188	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.188	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.188	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.189	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.189	5772	3	tsv.cpp	126	p(0x0133FC5C) = 95(0x0000005F)
20:04:19.189	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.189	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.189	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.186	4264	3	tsv.cpp	126	p(0x0153FC5C) = 37(0x00000025)
20:04:19.189	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.189	4264	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.189	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.189	4264	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.189	5772	3	tsv.cpp	126	p(0x0133FC5C) = 97(0x00000061)
20:04:19.189	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.189	4264	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.189	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.189	4264	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.189	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.189	4264	4	tsv.cpp	113	△if (pn) == false;
20:04:19.189	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.189	4264	3	tsv.cpp	126	p(0x0153FC5C) = 39(0x00000027)
20:04:19.189	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.189	4264	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.189	5772	3	tsv.cpp	126	p(0x0133FC5C) = 99(0x00000063)
20:04:19.189	4264	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.189	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.189	4264	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.189	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.189	4264	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.189	5772	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.189	4264	4	tsv.cpp	113	△if (pn) == false;
20:04:19.189	5772	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.189	4264	3	tsv.cpp	126	p(0x0153FC5C) = 41(0x00000029)
20:04:19.189	5772	4	tsv.cpp	113	△if (pn) == false;
20:04:19.189	4264	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.189	5772	3	tsv.cpp	126	p(0x0133FC5C) = 101(0x00000065)
20:04:19.189	4264	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.189	5772	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.189	4264	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.189	5772	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.189	4264	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.189	5772	2	tsv.cpp	111	▽if (current %p) == false;
20:04:19.189	4264	4	tsv.cpp	113	△if (pn) == false;
20:04:19.189	5772	3	tsv.cpp	135	current(0x0133FD9C) = 1(0x00000001)
20:04:19.189	4264	3	tsv.cpp	126	p(0x0153FC5C) = 43(0x0000002B)
20:04:19.189	5772	3	tsv.cpp	140	pn(0x0133FC54) = 1(0x00000001)
20:04:19.189	4264	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.189	5772	3	tsv.cpp	111	△if (current %p) == false;
20:04:19.189	4264	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.189	5772	2	tsv.cpp	109	while (1 &lt; current) == false;
20:04:19.189	4264	2	tsv.cpp	111	▽if (current %p) == false;
20:04:19.189	5772	2	tsv.cpp	144	▽if (1 &lt; pn) == false;
20:04:19.189	4264	3	tsv.cpp	135	current(0x0153FD9C) = 1(0x00000001)
20:04:19.189	5772	3	tsv.cpp	144	△if (1 &lt; pn) == false;
20:04:19.189	4264	3	tsv.cpp	140	pn(0x0153FC54) = 1(0x00000001)
20:04:19.189	5772	2	tsv.cpp	104	△if (1 &lt; current) == true;
20:04:19.189	4264	3	tsv.cpp	111	△if (current %p) == false;
20:04:19.189	4264	2	tsv.cpp	109	while (1 &lt; current) == false;
20:04:19.189	4264	2	tsv.cpp	144	▽if (1 &lt; pn) == false;
20:04:19.189	4264	3	tsv.cpp	144	△if (1 &lt; pn) == false;
20:04:19.189	4264	2	tsv.cpp	104	△if (1 &lt; current) == true;
20:04:19.189	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.189	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.189	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.189	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.189	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.189	868	3	tsv.cpp	126	p(0x0143FC5C) = 7(0x00000007)
20:04:19.189	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.189	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.189	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.189	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.189	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.189	868	3	tsv.cpp	126	p(0x0143FC5C) = 9(0x00000009)
20:04:19.189	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.189	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.189	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.189	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.190	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.190	868	3	tsv.cpp	126	p(0x0143FC5C) = 11(0x0000000B)
20:04:19.190	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.190	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.190	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.190	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.190	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.190	868	3	tsv.cpp	126	p(0x0143FC5C) = 13(0x0000000D)
20:04:19.190	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.190	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.190	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.190	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.190	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.190	868	3	tsv.cpp	126	p(0x0143FC5C) = 15(0x0000000F)
20:04:19.190	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.190	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.190	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.190	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.190	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.190	868	3	tsv.cpp	126	p(0x0143FC5C) = 17(0x00000011)
20:04:19.190	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.190	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.190	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.190	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.190	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.190	868	3	tsv.cpp	126	p(0x0143FC5C) = 19(0x00000013)
20:04:19.190	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.190	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.190	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.190	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.190	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.190	868	3	tsv.cpp	126	p(0x0143FC5C) = 21(0x00000015)
20:04:19.190	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.190	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.190	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.190	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.190	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.190	868	3	tsv.cpp	126	p(0x0143FC5C) = 23(0x00000017)
20:04:19.190	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.190	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.190	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.190	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.190	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.190	5772	1	tsv.cpp	154	return
20:04:19.190	5772	1	tsv.cpp	161	return
20:04:19.190	5772	1	bug.h	2468	日付＆時刻：2008-02-24(日) 20:04:19.190
20:04:19.190	5772	1	bug.h	2469	△bugbeard session root
20:04:19.190	868	3	tsv.cpp	126	p(0x0143FC5C) = 25(0x00000019)
20:04:19.191	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.191	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.191	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.191	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.191	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.191	868	3	tsv.cpp	126	p(0x0143FC5C) = 27(0x0000001B)
20:04:19.191	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.191	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.191	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.191	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.191	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.191	868	3	tsv.cpp	126	p(0x0143FC5C) = 29(0x0000001D)
20:04:19.191	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.191	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.191	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.191	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.191	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.191	868	3	tsv.cpp	126	p(0x0143FC5C) = 31(0x0000001F)
20:04:19.191	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.191	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.191	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.191	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.191	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.191	868	3	tsv.cpp	126	p(0x0143FC5C) = 33(0x00000021)
20:04:19.191	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.191	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.191	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.191	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.191	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.191	868	3	tsv.cpp	126	p(0x0143FC5C) = 35(0x00000023)
20:04:19.191	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.191	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.191	4264	1	tsv.cpp	154	return
20:04:19.191	4264	1	tsv.cpp	161	return
20:04:19.191	4264	1	bug.h	2468	日付＆時刻：2008-02-24(日) 20:04:19.191
20:04:19.191	4264	1	bug.h	2469	△bugbeard session root
20:04:19.191	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.191	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.191	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.191	868	3	tsv.cpp	126	p(0x0143FC5C) = 37(0x00000025)
20:04:19.191	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.191	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.191	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.191	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.191	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.191	868	3	tsv.cpp	126	p(0x0143FC5C) = 39(0x00000027)
20:04:19.192	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.192	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.192	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.192	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.192	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.192	868	3	tsv.cpp	126	p(0x0143FC5C) = 41(0x00000029)
20:04:19.192	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.192	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.192	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.192	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.192	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.192	868	3	tsv.cpp	126	p(0x0143FC5C) = 43(0x0000002B)
20:04:19.192	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.192	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.192	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.192	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.192	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.192	868	3	tsv.cpp	126	p(0x0143FC5C) = 45(0x0000002D)
20:04:19.192	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.192	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.192	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.192	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.192	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.192	868	3	tsv.cpp	126	p(0x0143FC5C) = 47(0x0000002F)
20:04:19.192	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.192	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.192	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.192	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.192	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.192	868	3	tsv.cpp	126	p(0x0143FC5C) = 49(0x00000031)
20:04:19.192	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.192	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.192	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.192	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.192	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.192	868	3	tsv.cpp	126	p(0x0143FC5C) = 51(0x00000033)
20:04:19.192	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.192	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.192	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.192	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.192	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.192	868	3	tsv.cpp	126	p(0x0143FC5C) = 53(0x00000035)
20:04:19.192	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.192	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.192	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.192	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.192	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.192	868	3	tsv.cpp	126	p(0x0143FC5C) = 55(0x00000037)
20:04:19.192	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.192	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.192	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.192	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.192	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.192	868	3	tsv.cpp	126	p(0x0143FC5C) = 57(0x00000039)
20:04:19.192	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.192	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.192	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.192	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.192	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.192	868	3	tsv.cpp	126	p(0x0143FC5C) = 59(0x0000003B)
20:04:19.193	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.193	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.193	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.193	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.193	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.193	868	3	tsv.cpp	126	p(0x0143FC5C) = 61(0x0000003D)
20:04:19.193	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.193	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.193	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.193	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.193	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.193	868	3	tsv.cpp	126	p(0x0143FC5C) = 63(0x0000003F)
20:04:19.193	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.193	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.193	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.193	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.193	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.193	868	3	tsv.cpp	126	p(0x0143FC5C) = 65(0x00000041)
20:04:19.193	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.193	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.193	868	2	tsv.cpp	111	▽if (current %p) == true;
20:04:19.193	868	3	tsv.cpp	113	▽if (pn) == false;
20:04:19.193	868	4	tsv.cpp	113	△if (pn) == false;
20:04:19.193	868	3	tsv.cpp	126	p(0x0143FC5C) = 67(0x00000043)
20:04:19.193	868	3	tsv.cpp	111	△if (current %p) == true;
20:04:19.193	868	2	tsv.cpp	109	while (1 &lt; current) == true;
20:04:19.193	868	2	tsv.cpp	111	▽if (current %p) == false;
20:04:19.193	868	3	tsv.cpp	135	current(0x0143FD9C) = 1(0x00000001)
20:04:19.193	868	3	tsv.cpp	140	pn(0x0143FC54) = 1(0x00000001)
20:04:19.193	868	3	tsv.cpp	111	△if (current %p) == false;
20:04:19.193	868	2	tsv.cpp	109	while (1 &lt; current) == false;
20:04:19.193	868	2	tsv.cpp	144	▽if (1 &lt; pn) == false;
20:04:19.193	868	3	tsv.cpp	144	△if (1 &lt; pn) == false;
20:04:19.193	868	2	tsv.cpp	104	△if (1 &lt; current) == true;
20:04:19.194	868	1	tsv.cpp	154	return
20:04:19.194	868	1	tsv.cpp	161	return
20:04:19.194	868	1	bug.h	2468	日付＆時刻：2008-02-24(日) 20:04:19.194
20:04:19.194	868	1	bug.h	2469	△bugbeard session root
20:04:19.194	540	2	tsv.cpp	184	△for
20:04:19.194	540	1	tsv.cpp	189	▽delete
20:04:19.194	540	2	tsv.cpp	189	△delete
20:04:19.194	540	1	tsv.cpp	191	return
20:04:19.194	540	1	bug.h	2468	日付＆時刻：2008-02-24(日) 20:04:19.194
20:04:19.194	540	1	bug.h	2469	△bugbeard session root
</PRE>
</DIV>

#### 解説

上記の出力結果は...

<DIV class="sample">
<PRE>
20:04:19.183	540	1	bug.h	2849	▽Commandline Argument Information
20:04:19.183	540	2	bug.h	2850	argc(0x0012FAC8) = 4(0x00000004)
20:04:19.183	540	2	bug.h	2853	args[0]:tsv
20:04:19.183	540	2	bug.h	2853	args[1]:101
20:04:19.183	540	2	bug.h	2853	args[2]:201
20:04:19.183	540	2	bug.h	2853	args[3]:301
20:04:19.183	540	2	bug.h	2849	△Commandline Argument Information
</PRE>
</DIV>

...を見てもおわかりいただけますが、「101 201 301」を引数として与えた場合のものです。
またこのケースでは .tsv の各カラムはそれぞれ 時刻, スレッドID, ネストの深さ, __FILE__, __LINE__, ログメッセージ の内容になっていますが、コンパイル時の状況によりこの書式は若干変化します。

このサンプルでの一つ目の肝は...

<DIV class="sample">
<span class="SpanClass2">//&nbsp;&nbsp;標準エラーにTSV形式の出力を行うロガーの定義(メインスレッド用)<br/></span>
<span class="SpanClass11">BUG_define_logger</span><span class="SpanClass10">(</span><span class="SpanClass5">new</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_tsv_logger</span><span class="SpanClass10">(</span><span class="SpanClass11">common_writer</span><span class="SpanClass10">));</span>
</DIV>

...で、ツリー形式ではなく .tsv 形式のログ出力を指定しているところです。ロガーへの引数がこれまでのサンプルと違いますが、これはマルチスレッド対応の為のもので、.tsv 形式でログ出力を行うこととは本質的には関係ありません。

このサンプルでの二つの肝は最初に bug.h を include する前に...
        
<DIV class="sample">
<span class="SpanClass9">#define&nbsp;BUG_EVIL_CONTRACT&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;"悪魔の契約"<br/></span>
<span class="SpanClass9">#define&nbsp;BUG_MULTI_THREAD&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;マルチスレッドモデルでバグベアードを利用<br/></span>
<span class="SpanClass9">#include&nbsp;"bug.h"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;ロガーを定義する為にステートメントハックを有効にしない状態で include<br/></span>
</DIV>

BUG_MULTI_THREAD マクロを定義してバグベアードをマルチスレッドモデルで利用すること宣言した上で、ロガーを...
        
<DIV class="sample">
<span class="SpanClass2">//&nbsp;&nbsp;共用ライターの定義<br/>
</span><span class="SpanClass11">BUG_exec</span><span class="SpanClass10">(</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_smart_writer</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">common_writer</span><span class="SpanClass10">(</span><span class="SpanClass5">new</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_file_writer_base</span><span class="SpanClass10">(</span><span class="SpanClass11">stderr</span><span class="SpanClass10">)));</span><span class="SpanClass0"><br/>
<br/>
</span><span class="SpanClass2">//&nbsp;&nbsp;標準エラーにTSV形式の出力を行うロガーの定義(メインスレッド用)<br/>
</span><span class="SpanClass11">BUG_define_logger</span><span class="SpanClass10">(</span><span class="SpanClass5">new</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_tsv_logger</span><span class="SpanClass10">(</span><span class="SpanClass11">common_writer</span><span class="SpanClass10">));</span>
</DIV>

<DIV class="sample">
<span class="SpanClass11">BUG_THREAD_RESULT</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">BUG_THREAD_CALL</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">factorize_thread</span><span class="SpanClass10">(</span><span class="SpanClass16">void</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">*</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">data</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]スレッドローカルロガーの定義<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_define_logger</span><span class="SpanClass10">(</span><span class="SpanClass5">new</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_tsv_logger</span><span class="SpanClass10">(</span><span class="SpanClass11">common_writer</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">factorize</span><span class="SpanClass10">((</span><span class="SpanClass16">int</span><span class="SpanClass10">)</span><span class="SpanClass11">data</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">return</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass4">0</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
</span><span class="SpanClass10">}</span>
</DIV>
        
...のように各スレッド毎に定義していることです。バグベアードをマルチスレッドなプログラムで利用する場合は必ずこのように各スレッド毎にロガーを定義してください。ロガーが定義されていないスレッドではログ出力が行われません。

このサンプルでは同じ出力先へログ出力を行うので bugbeard::bug_smart_writer 型でラップした bugbeard::bug_writer 派生オブジェクトを各スレッドで使いまわしています。これはロガーが自分に与えられた bugbeard::bug_writer 派生オブジェクトを自身のデストラクタ内で破棄する為です。bugbeard::bug_smart_writer 型でラップしないと最初に終了したスレッドにより bugbeard::bug_writer 派生オブジェクトが破棄され残りのスレッドが既に破棄されたオブジェクトを使用してログ出力を行おうとして異常終了します。

マルチプロセス/マルチスレッドな状況ではツリー形式より.tsv形式のほうが有効だろうと思って.tsv形式での出力にも対応したもののフィルターの使えるビューアで見る分にはマルチプロセス/マルチスレッドな状況であっても.tsv形式よりもツリー形式のほうが見やすかったりします。でも、まぁ、.tsv形式はデータとして処理し易いんで統計的な情報分析やる際に役立ってくれると思います。
        
<A name="step4"></A>
### バルクログ出力サンプル
#### サンプルコード
<DIV class="sample">
<span class="SpanClass3">/******************************************************************************<br/>
&nbsp;&nbsp;&nbsp;&nbsp;バグベアード&nbsp;-bugbeard-<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;サンプル&nbsp;"bulklog.cpp"&nbsp;ソースファイル<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Coded&nbsp;by&nbsp;Wraith&nbsp;in&nbsp;Feb&nbsp;18,&nbsp;2007.<br/>
******************************************************************************/</span><span class="SpanClass0"><br/>
<br/>
<br/>
</span><span class="SpanClass2">///////////////////////////////////////////////////////////////////////////////<br/>
//<br/>
//&nbsp;&nbsp;includes<br/>
//<br/>
</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#include&nbsp;&lt;stdio.h&gt;<br/>
#include&nbsp;&lt;stdlib.h&gt;<br/>
</span><span class="SpanClass0"><br/>
<br/>
</span><span class="SpanClass2">///////////////////////////////////////////////////////////////////////////////<br/>
//<br/>
//&nbsp;&nbsp;[BUG]bugbeard<br/>
//<br/>
</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#if&nbsp;defined(NDEBUG)<br/>
#define&nbsp;BUG_DISABLE_BUGBEARD&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;リリース版ではバグベアードをロードしない<br/>
</span><span class="SpanClass9">#endif<br/>
</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#define&nbsp;BUG_EVIL_CONTRACT&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;"悪魔の契約"<br/>
</span><span class="SpanClass9">#include&nbsp;"bug.h"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;ロガーを定義する為にステートメントハックを有効にしない状態で&nbsp;include<br/>
</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#if&nbsp;defined(BUG_LOAD_BUGBEARD)<br/>
</span><span class="SpanClass16">const</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_string</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bug_log_filename</span><span class="SpanClass10">()</span><span class="SpanClass0"><br/>
</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">using</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass5">namespace</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass16">const</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bug_clock</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">stamp</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bug_clock</span><span class="SpanClass10">();</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#if&nbsp;defined(__MWERKS__)<br/>
#error&nbsp;なんか Metrowerk のコンパイラはこのへんのコードの解釈の仕方が、びっくりするぐらいバカで付き合いきれません。(´Д｀；)<br/>
#endif<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">return</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">bug_dir</span><span class="SpanClass10">(</span><span class="SpanClass6">"buglog"</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">+</span><span class="SpanClass11">bug_dir</span><span class="SpanClass10">(</span><span class="SpanClass6">"%4.4d"</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">stamp</span><span class="SpanClass10">.</span><span class="SpanClass11">year</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">+</span><span class="SpanClass11">bug_dir</span><span class="SpanClass10">(</span><span class="SpanClass6">"%2.2d"</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">stamp</span><span class="SpanClass10">.</span><span class="SpanClass11">mon</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">+</span><span class="SpanClass11">bug_dir</span><span class="SpanClass10">(</span><span class="SpanClass6">"%2.2d"</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">stamp</span><span class="SpanClass10">.</span><span class="SpanClass11">mday</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">+</span><span class="SpanClass6">"bulklog.log"</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#endif<br/>
</span><span class="SpanClass0"><br/>
</span><span class="SpanClass2">//&nbsp;&nbsp;ログファイルにツリー形式の出力を行うロガーの定義<br/>
</span><span class="SpanClass11">BUG_define_logger</span><span class="SpanClass10">(</span><span class="SpanClass5">new</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_tree_logger</span><span class="SpanClass10">(</span><span class="SpanClass5">new</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_file_writer</span><span class="SpanClass10">(</span><span class="SpanClass11">bug_log_filename</span><span class="SpanClass10">())));</span><span class="SpanClass0"><br/>
<br/>
</span><span class="SpanClass9">#define&nbsp;BUG_STATEMENT_HACK&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;ステートメントハックの設定<br/>
</span><span class="SpanClass9">#include&nbsp;"bug.h"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;ステートメントハックを有効にする為、再度&nbsp;include<br/>
</span><span class="SpanClass0"><br/>
<br/>
</span><span class="SpanClass2">///////////////////////////////////////////////////////////////////////////////<br/>
//<br/>
//&nbsp;&nbsp;user&nbsp;codes<br/>
//<br/>
</span><span class="SpanClass0"><br/>
</span><span class="SpanClass2">//<br/>
//&nbsp;&nbsp;素因数分解<br/>
//<br/>
</span><span class="SpanClass16">void</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">factorize</span><span class="SpanClass10">(</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">number</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">printf</span><span class="SpanClass10">(</span><span class="SpanClass6">"%d&nbsp;=&nbsp;"</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">number</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">current</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">number</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">if</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">(</span><span class="SpanClass4">1</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">&lt;</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">current</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">p</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass4">2</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">pn</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass4">0</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">inc</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass4">1</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">while</span><span class="SpanClass10">(</span><span class="SpanClass4">1</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">&lt;</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">current</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">if</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">(</span><span class="SpanClass11">current</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">%</span><span class="SpanClass11">p</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">if</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">(</span><span class="SpanClass11">pn</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">printf</span><span class="SpanClass10">(</span><span class="SpanClass6">"%d"</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">p</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">if</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">(</span><span class="SpanClass4">1</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">&lt;</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">pn</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">printf</span><span class="SpanClass10">(</span><span class="SpanClass6">"^%d"</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">pn</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">printf</span><span class="SpanClass10">(</span><span class="SpanClass6">"&nbsp;*&nbsp;"</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">pn</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass4">0</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">p</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">+=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">inc</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]値のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_puts</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_VAL</span><span class="SpanClass10">(</span><span class="SpanClass11">p</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">inc</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass4">2</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">else</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">current</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">/=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">p</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]値のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_puts</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_VAL</span><span class="SpanClass10">(</span><span class="SpanClass11">current</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">++</span><span class="SpanClass11">pn</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]値のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_puts</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_VAL</span><span class="SpanClass10">(</span><span class="SpanClass11">pn</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">printf</span><span class="SpanClass10">(</span><span class="SpanClass6">"%d"</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">p</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">if</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">(</span><span class="SpanClass4">1</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">&lt;</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">pn</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">printf</span><span class="SpanClass10">(</span><span class="SpanClass6">"^%d"</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">pn</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">else</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">printf</span><span class="SpanClass10">(</span><span class="SpanClass6">"%d"</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">current</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">printf</span><span class="SpanClass10">(</span><span class="SpanClass6">"\n"</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">return</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
<br/>
</span><span class="SpanClass2">//<br/>
//&nbsp;&nbsp;スタートアップ<br/>
//<br/>
</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">main</span><span class="SpanClass10">(</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">argc</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass16">char</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">*</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">args</span><span class="SpanClass10">[])</span><span class="SpanClass0"><br/>
</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]コンパイル情報のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_exec</span><span class="SpanClass10">(</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_compile_info</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_LOG</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
<br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]コマンドライン引数のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_exec</span><span class="SpanClass10">(</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_arg_info</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_LOG</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">argc</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">args</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;<br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">for</span><span class="SpanClass10">(</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">i</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass4">1</span><span class="SpanClass10">;</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">i</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">&lt;</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">argc</span><span class="SpanClass10">;</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">++</span><span class="SpanClass11">i</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">factorize</span><span class="SpanClass10">(</span><span class="SpanClass11">atoi</span><span class="SpanClass10">(</span><span class="SpanClass11">args</span><span class="SpanClass10">[</span><span class="SpanClass11">i</span><span class="SpanClass10">]));</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;<br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">return</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">EXIT_SUCCESS</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
<br/>
<br/>
</span><span class="SpanClass3">/******************************************************************************<br/>
&nbsp;&nbsp;&nbsp;&nbsp;□■□■&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Wraith&nbsp;the&nbsp;Trickster&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;□■□■<br/>
&nbsp;&nbsp;&nbsp;&nbsp;■□■□&nbsp;～I'll&nbsp;go&nbsp;with&nbsp;heaven's&nbsp;advantage&nbsp;and&nbsp;fool's&nbsp;wisdom.～&nbsp;■□■□<br/>
******************************************************************************/</span><span class="SpanClass0"><br/>
</span>
</DIV>
#### 出力結果(./buglog/YYYY/MM/DD/bulklog.log)
        ./buglog/YYYY/MM/DD/bulklog.log なパスにファイルとして出力されることを除けば内容的には先の tsv.cpp によるログ出力とあまり変わり映えしないので割愛。

#### 解説
        <P>
        このサンプルのコードでは日付別のディレクトリにログファイルを出力します。
<DIV class="sample">
<span class="SpanClass9">#if&nbsp;defined(BUG_LOAD_BUGBEARD)<br/>
</span><span class="SpanClass16">const</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_string</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bug_log_filename</span><span class="SpanClass10">()</span><span class="SpanClass0"><br/>
</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">using</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass5">namespace</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass16">const</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bug_clock</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">stamp</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bug_clock</span><span class="SpanClass10">();</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#if&nbsp;defined(__MWERKS__)<br/>
#error&nbsp;なんか Metrowerk のコンパイラはこのへんのコードの解釈の仕方が、びっくりするぐらいバカで付き合いきれません。(´Д｀；)<br/>
#endif<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">return</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">bug_dir</span><span class="SpanClass10">(</span><span class="SpanClass6">"buglog"</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">+</span><span class="SpanClass11">bug_dir</span><span class="SpanClass10">(</span><span class="SpanClass6">"%4.4d"</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">stamp</span><span class="SpanClass10">.</span><span class="SpanClass11">year</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">+</span><span class="SpanClass11">bug_dir</span><span class="SpanClass10">(</span><span class="SpanClass6">"%2.2d"</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">stamp</span><span class="SpanClass10">.</span><span class="SpanClass11">mon</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">+</span><span class="SpanClass11">bug_dir</span><span class="SpanClass10">(</span><span class="SpanClass6">"%2.2d"</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">stamp</span><span class="SpanClass10">.</span><span class="SpanClass11">mday</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">+</span><span class="SpanClass6">"bulklog.log"</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#endif<br/>
</span><span class="SpanClass0"><br/>
</span><span class="SpanClass2">//&nbsp;&nbsp;標準エラーにツリー形式の出力を行うロガーの定義<br/>
</span><span class="SpanClass11">BUG_define_logger</span><span class="SpanClass10">(</span><span class="SpanClass5">new</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_tree_logger</span><span class="SpanClass10">(</span><span class="SpanClass5">new</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">bugbeard</span><span class="SpanClass10">::</span><span class="SpanClass11">bug_file_writer</span><span class="SpanClass10">(</span><span class="SpanClass11">bug_log_filename</span><span class="SpanClass10">())));</span>
</DIV>
        bugbeard::bug_dir はディレクトリを自動で作成しつつパス文字列を形成するユーティリティです。
        </P>


<A name="step5"></A>
### プロファイル＆カバレッジ測定サンプル
#### サンプルコード
<DIV class="sample">
<span class="SpanClass3">/******************************************************************************<br/>
&nbsp;&nbsp;&nbsp;&nbsp;バグベアード&nbsp;-bugbeard-<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;サンプル&nbsp;"profile.cpp"&nbsp;ソースファイル<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Coded&nbsp;by&nbsp;Wraith&nbsp;in&nbsp;Sep&nbsp;16,&nbsp;2008.<br/>
******************************************************************************/</span><span class="SpanClass0"><br/>
<br/>
<br/>
</span><span class="SpanClass2">///////////////////////////////////////////////////////////////////////////////<br/>
//<br/>
//&nbsp;&nbsp;includes<br/>
//<br/>
</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#include&nbsp;&lt;stdio.h&gt;<br/>
#include&nbsp;&lt;stdlib.h&gt;<br/>
</span><span class="SpanClass0"><br/>
<br/>
</span><span class="SpanClass2">///////////////////////////////////////////////////////////////////////////////<br/>
//<br/>
//&nbsp;&nbsp;[BUG]bugbeard<br/>
//<br/>
</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#if&nbsp;!defined(NDEBUG)<br/>
#define&nbsp;BUG_EVIL_CONTRACT&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;"悪魔の契約"<br/>
</span><span class="SpanClass9">#endif<br/>
</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#if&nbsp;defined(BUG_EVIL_CONTRACT)<br/>
#&nbsp;&nbsp;&nbsp;define&nbsp;BUG_DEFINE_GLOBAL_LOGGER&nbsp;&nbsp;&nbsp;&nbsp;new&nbsp;bugbeard::bug_tree_logger(new&nbsp;bugbeard::bug_file_writer("trace.log"))<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;"trace.log" へツリー形式の出力を行うロガーの定義<br/>
</span><NOBR><span class="SpanClass9">#&nbsp;&nbsp;&nbsp;define&nbsp;BUG_DEFINE_GLOBAL_PROFILER&nbsp;&nbsp;new&nbsp;bugbeard::bug_tsv_profiler(new&nbsp;bugbeard::bug_file_writer("profile.tsv"),&nbsp;new&nbsp;bugbeard::bug_file_writer("coverage.tsv"))</span></NOBR><br/>
<NOBR><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;"profile.tsv" へプロファイル結果の出力を、"coverage.tsv" へカバレッジ測定結果の出力を行うプロファイルロガーの定義</span></NOBR><br/>
<span class="SpanClass9">#&nbsp;&nbsp;&nbsp;define&nbsp;BUG_STATEMENT_HACK&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;ステートメントハックの設定<br/>
</span><span class="SpanClass9">#&nbsp;&nbsp;&nbsp;include&nbsp;"bug.h"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;ステートメントハックを有効にする為、再度 include<br/>
</span><span class="SpanClass9">#endif<br/>
</span><span class="SpanClass0"><br/>
<br/>
</span><span class="SpanClass2">///////////////////////////////////////////////////////////////////////////////<br/>
//<br/>
//&nbsp;&nbsp;user&nbsp;codes<br/>
//<br/>
</span><span class="SpanClass0"><br/>
</span><span class="SpanClass2">//<br/>
//&nbsp;&nbsp;素因数分解<br/>
//<br/>
</span><span class="SpanClass16">void</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">factorize</span><span class="SpanClass10">(</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">number</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">printf</span><span class="SpanClass10">(</span><span class="SpanClass6">"%d&nbsp;=&nbsp;"</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">number</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">current</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">number</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">if</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">(</span><span class="SpanClass4">1</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">&lt;</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">current</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">p</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass4">2</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">pn</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass4">0</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">inc</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass4">1</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">while</span><span class="SpanClass10">(</span><span class="SpanClass4">1</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">&lt;</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">current</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">if</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">(</span><span class="SpanClass11">current</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">%</span><span class="SpanClass11">p</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">if</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">(</span><span class="SpanClass11">pn</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">printf</span><span class="SpanClass10">(</span><span class="SpanClass6">"%d"</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">p</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">if</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">(</span><span class="SpanClass4">1</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">&lt;</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">pn</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">printf</span><span class="SpanClass10">(</span><span class="SpanClass6">"^%d"</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">pn</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">printf</span><span class="SpanClass10">(</span><span class="SpanClass6">"&nbsp;*&nbsp;"</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">pn</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass4">0</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">p</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">+=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">inc</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]値のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_puts</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_VAL</span><span class="SpanClass10">(</span><span class="SpanClass11">p</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">inc</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass4">2</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">else</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">current</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">/=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">p</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]値のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_puts</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_VAL</span><span class="SpanClass10">(</span><span class="SpanClass11">current</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">++</span><span class="SpanClass11">pn</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;[BUG]値のログ出力<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_puts</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_VAL</span><span class="SpanClass10">(</span><span class="SpanClass11">pn</span><span class="SpanClass10">));</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">printf</span><span class="SpanClass10">(</span><span class="SpanClass6">"%d"</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">p</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">if</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">(</span><span class="SpanClass4">1</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">&lt;</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">pn</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">printf</span><span class="SpanClass10">(</span><span class="SpanClass6">"^%d"</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">pn</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">else</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">printf</span><span class="SpanClass10">(</span><span class="SpanClass6">"%d"</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">current</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">printf</span><span class="SpanClass10">(</span><span class="SpanClass6">"\n"</span><span class="SpanClass10">);</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">return</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
<br/>
<br/>
</span><span class="SpanClass2">//<br/>
//&nbsp;&nbsp;スタートアップ<br/>
//<br/>
</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">main</span><span class="SpanClass10">(</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">argc</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass16">char</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">*</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">args</span><span class="SpanClass10">[])</span><span class="SpanClass0"><br/>
</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">for</span><span class="SpanClass10">(</span><span class="SpanClass16">int</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">i</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass4">1</span><span class="SpanClass10">;</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">i</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">&lt;</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">argc</span><span class="SpanClass10">;</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">++</span><span class="SpanClass11">i</span><span class="SpanClass10">)</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">{</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">factorize</span><span class="SpanClass10">(</span><span class="SpanClass11">atoi</span><span class="SpanClass10">(</span><span class="SpanClass11">args</span><span class="SpanClass10">[</span><span class="SpanClass11">i</span><span class="SpanClass10">]));</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
&nbsp;&nbsp;&nbsp;&nbsp;<br/>
&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass5">return</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">EXIT_SUCCESS</span><span class="SpanClass10">;</span><span class="SpanClass0"><br/>
</span><span class="SpanClass10">}</span><span class="SpanClass0"><br/>
<br/>
<br/>
</span><span class="SpanClass3">/******************************************************************************<br/>
&nbsp;&nbsp;&nbsp;&nbsp;□■□■&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Wraith&nbsp;the&nbsp;Trickster&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;□■□■<br/>
&nbsp;&nbsp;&nbsp;&nbsp;■□■□&nbsp;～I'll&nbsp;go&nbsp;with&nbsp;heaven's&nbsp;advantage&nbsp;and&nbsp;fool's&nbsp;wisdom.～&nbsp;■□■□<br/>
******************************************************************************/</span><span class="SpanClass0"><br/>
</span>
</DIV>
#### 出力結果( trace.log )
<DIV class="sample">
<PRE>
┌──────────────────────────────────────
│日付＆時刻：2008-09-17(水) 07:07:06.587
└─────┬────────────────────────────────
07:07:06.587├┬▽for <profile.cpp>#107
07:07:06.587│├┬▽if (1 < current) == true; <profile.cpp>#48
07:07:06.587││├・while (1 < current) == true; <profile.cpp>#53
07:07:06.587││├┬▽if (current %p) == false; <profile.cpp>#55
07:07:06.587│││├・current(0x0012E6F0) = 3(0x00000003) <profile.cpp>#79
07:07:06.587│││├・pn(0x0012E50C) = 1(0x00000001) <profile.cpp>#84
07:07:06.587│││└△if (current %p) == false; <profile.cpp>#55
07:07:06.587││├・while (1 < current) == true; <profile.cpp>#53
07:07:06.587││├┬▽if (current %p) == true; <profile.cpp>#55
07:07:06.587│││├┬▽if (pn) == true; <profile.cpp>#57
07:07:06.587││││├┬▽if (1 < pn) == false; <profile.cpp>#60
07:07:06.587│││││└△if (1 < pn) == false; <profile.cpp>#60
07:07:06.587││││└△if (pn) == true; <profile.cpp>#57
07:07:06.587│││├・p(0x0012E510) = 3(0x00000003) <profile.cpp>#70
07:07:06.587│││└△if (current %p) == true; <profile.cpp>#55
07:07:06.587││├・while (1 < current) == true; <profile.cpp>#53
07:07:06.587││├┬▽if (current %p) == false; <profile.cpp>#55
07:07:06.587│││├・current(0x0012E6F0) = 1(0x00000001) <profile.cpp>#79
07:07:06.587│││├・pn(0x0012E50C) = 1(0x00000001) <profile.cpp>#84
07:07:06.587│││└△if (current %p) == false; <profile.cpp>#55
07:07:06.587││├・while (1 < current) == false; <profile.cpp>#53
07:07:06.587││├┬▽if (1 < pn) == false; <profile.cpp>#88
07:07:06.587│││└△if (1 < pn) == false; <profile.cpp>#88
07:07:06.587││└△if (1 < current) == true; <profile.cpp>#48
07:07:06.587│├・return <profile.cpp>#98
07:07:06.587│└△for <profile.cpp>#107
07:07:06.587├・return <profile.cpp>#112
┌─────┴────────────────────────────────
│日付＆時刻：2008-09-17(水) 07:07:06.587
└──────────────────────────────────────
</PRE>
</DIV>
    
#### 出力結果( profile.tsv )
<DIV class="sample">
<PRE>
__FILE__	__LINE__	スコープ	合計総稼働時間	合計総バグ時間	合計総実働時間	合計自稼働時間	合計自バグ時間	合計自実働時間	合計子稼働時間	合計子バグ時間	合計子実働時間	コールカウント	平均総稼働時間	平均総バグ時間	平均総実働時間	平均自稼働時間	平均自バグ時間	平均自実働時間	平均子稼働時間	平均子バグ時間	平均子実働時間	最小スタンプ	最小総稼働時間	最小総バグ時間	最小総実働時間	最小自稼働時間	最小自バグ時間	最小自実働時間	最小子稼働時間	最小子バグ時間	最小子実働時間	最大スタンプ	最大総稼働時間	最大総バグ時間	最大総実働時間	最大自稼働時間	最大自バグ時間	最大自実働時間	最大子稼働時間	最大子バグ時間	最大子実働時間
@OVERALL_SCOPE	0	@OVERALL_SCOPE	0.003570	0.002757	0.003212	0.003570	0.000085	0.000000	0.001543	0.002672	0.003212	1	0.003570	0.002757	0.003212	0.003570	0.000085	0.000000	0.001543	0.002672	0.003212	@OVERALL_SCOPE	0.003570	0.002757	0.003212	0.003570	0.000085	0.000000	0.001543	0.002672	0.003212	@OVERALL_SCOPE	0.003570	0.002757	0.003212	0.003570	0.000085	0.000000	0.001543	0.002672	0.003212
profile.cpp	48	if (1 < current) == true;	0.001865	0.002458	0.001882	0.001865	0.000382	0.001482	0.000969	0.002075	0.000399	1	0.001865	0.002458	0.001882	0.001865	0.000382	0.001482	0.000969	0.002075	0.000399	07:07:06.587	0.001865	0.002458	0.001882	0.001865	0.000382	0.001482	0.000969	0.002075	0.000399	07:07:06.587	0.001865	0.002458	0.001882	0.001865	0.000382	0.001482	0.000969	0.002075	0.000399
profile.cpp	55	if (current %p) == false;	0.000539	0.000507	0.000031	0.000539	0.000507	0.000031	0.000000	0.000000	0.000000	2	0.000269	0.000253	0.000015	0.000269	0.000253	0.000015	0.000000	0.000000	0.000000	07:07:06.587	0.000173	0.000166	0.000006	0.000173	0.000166	0.000006	0.000000	0.000000	0.000000	07:07:06.587	0.000365	0.000341	0.000024	0.000365	0.000341	0.000024	0.000000	0.000000	0.000000
profile.cpp	55	if (current %p) == true;	0.000304	0.001444	0.000365	0.000304	0.000142	0.000162	0.001351	0.001302	0.000202	1	0.000304	0.001444	0.000365	0.000304	0.000142	0.000162	0.001351	0.001302	0.000202	07:07:06.587	0.000304	0.001444	0.000365	0.000304	0.000142	0.000162	0.001351	0.001302	0.000202	07:07:06.587	0.000304	0.001444	0.000365	0.000304	0.000142	0.000162	0.001351	0.001302	0.000202
profile.cpp	57	if (pn) == true;	0.001351	0.001302	0.000202	0.001351	0.001150	0.000200	0.000153	0.000151	0.000002	1	0.001351	0.001302	0.000202	0.001351	0.001150	0.000200	0.000153	0.000151	0.000002	07:07:06.587	0.001351	0.001302	0.000202	0.001351	0.001150	0.000200	0.000153	0.000151	0.000002	07:07:06.587	0.001351	0.001302	0.000202	0.001351	0.001150	0.000200	0.000153	0.000151	0.000002
profile.cpp	60	if (1 < pn) == false;	0.000153	0.000151	0.000002	0.000153	0.000151	0.000002	0.000000	0.000000	0.000000	1	0.000153	0.000151	0.000002	0.000153	0.000151	0.000002	0.000000	0.000000	0.000000	07:07:06.587	0.000153	0.000151	0.000002	0.000153	0.000151	0.000002	0.000000	0.000000	0.000000	07:07:06.587	0.000153	0.000151	0.000002	0.000153	0.000151	0.000002	0.000000	0.000000	0.000000
profile.cpp	88	if (1 < pn) == false;	0.000125	0.000123	0.000002	0.000125	0.000123	0.000002	0.000000	0.000000	0.000000	1	0.000125	0.000123	0.000002	0.000125	0.000123	0.000002	0.000000	0.000000	0.000000	07:07:06.587	0.000125	0.000123	0.000002	0.000125	0.000123	0.000002	0.000000	0.000000	0.000000	07:07:06.587	0.000125	0.000123	0.000002	0.000125	0.000123	0.000002	0.000000	0.000000	0.000000
profile.cpp	107	for	0.001543	0.002672	0.003212	0.001543	0.000213	0.001330	0.001865	0.002458	0.001882	1	0.001543	0.002672	0.003212	0.001543	0.000213	0.001330	0.001865	0.002458	0.001882	07:07:06.587	0.001543	0.002672	0.003212	0.001543	0.000213	0.001330	0.001865	0.002458	0.001882	07:07:06.587	0.001543	0.002672	0.003212	0.001543	0.000213	0.001330	0.001865	0.002458	0.001882
</PRE>
</DIV>
    <DIV class="comment">
        <IMG class="accessary" alt="Wraith the Trickster" src="/image/icon/wrth32.png">
        <P>
            タブ区切りテキストなんで普通にテキスト表示しただけだとカラムがずれた状態で表示されます。MS-Excel のシートに貼り付けるなり、その他のデータ形式に変換するなりしてご利用ください。
            各項目の意味については<A href="#profile-columns">リファレンス</A>を参照してください。
        </P>
        <P>
            このデータを元にプログラムの高速化を図る場合は、"合計自実働時間"順にソートし最も"合計自実働時間"が大きなスコープから高速化を検討するとよいでしょう。またその際には"最大スタンプ"や"最小スタンプ"を手がかりに、どういったフローの時に時間がかかって逆にどういったフローの時に時間がかかっていないのか参考にするのとよいでしょう。
        </P>
        <P>
            このプロファイルデータにはどうしても測定誤差というものがあることにご留意ください。特にコールカウントが大きなスコープの合計時間に関しては積み重なりにより誤差が大きくなる傾向があります。
        </P>
    </DIV>

#### 出力結果( coverage.tsv )
<DIV class="sample">
<PRE>
__FILE__	__LINE__	スコープ	コールカウント
profile.cpp	48	if (1 < current) == false;	0
profile.cpp	48	if (1 < current) == true;	1
profile.cpp	55	if (current %p) == false;	2
profile.cpp	55	if (current %p) == true;	1
profile.cpp	57	if (pn) == false;	0
profile.cpp	57	if (pn) == true;	1
profile.cpp	60	if (1 < pn) == false;	1
profile.cpp	60	if (1 < pn) == true;	0
profile.cpp	88	if (1 < pn) == false;	1
profile.cpp	88	if (1 < pn) == true;	0
</PRE>
</DIV>
    <DIV class="comment">
        <IMG class="accessary" alt="Wraith the Trickster" src="/image/icon/wrth32.png">
        <P>
            タブ区切りテキストなんで普通にテキスト表示しただけだとカラムがずれた状態で表示されます。MS-Excel のシートに貼り付けるなり、その他のデータ形式に変換するなりしてご利用ください。
        </P>
        <P>
            プロファイルのデータと異なり if スコープだけが抽出され、且つ if の条件式が true あるいは false のどちらか片方しかしか実行されなかった if スコープの実行されなかった側をコールカウントが 0 のデータとして挿入します。
        </P>
    </DIV>

#### 解説
        <P>
            このサンプルのコードでは以下の指定により、プロファイルおよびカバレッジの測定結果をそれぞれ "profile.tsv" および "coverage.tsv" に出力します。(＋メインのログを "trace.log" に出力します。 )
<DIV class="sample">
<span class="SpanClass9">#if&nbsp;!defined(NDEBUG)<br/>
#define&nbsp;BUG_EVIL_CONTRACT&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;"悪魔の契約"<br/>
</span><span class="SpanClass9">#endif<br/>
</span><span class="SpanClass0"><br/>
</span><span class="SpanClass9">#if&nbsp;defined(BUG_EVIL_CONTRACT)<br/>
#&nbsp;&nbsp;&nbsp;define&nbsp;BUG_DEFINE_GLOBAL_LOGGER&nbsp;&nbsp;&nbsp;&nbsp;new&nbsp;bugbeard::bug_tree_logger(new&nbsp;bugbeard::bug_file_writer("trace.log"))<br/>
</span><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;"trace.log" へツリー形式の出力を行うロガーの定義<br/>
</span><NOBR><span class="SpanClass9">#&nbsp;&nbsp;&nbsp;define&nbsp;BUG_DEFINE_GLOBAL_PROFILER&nbsp;&nbsp;new&nbsp;bugbeard::bug_tsv_profiler(new&nbsp;bugbeard::bug_file_writer("profile.tsv"),&nbsp;new&nbsp;bugbeard::bug_file_writer("coverage.tsv"))</span></NOBR><br/>
<NOBR><span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;"profile.tsv" へプロファイル結果の出力を、"coverage.tsv" へカバレッジ測定結果の出力を行うプロファイルロガーの定義</span></NOBR><br/>
<span class="SpanClass9">#&nbsp;&nbsp;&nbsp;define&nbsp;BUG_STATEMENT_HACK&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;ステートメントハックの設定<br/>
</span><span class="SpanClass9">#&nbsp;&nbsp;&nbsp;include&nbsp;"bug.h"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass2">//&nbsp;&nbsp;ステートメントハックを有効にする為、再度 include<br/>
</span><span class="SpanClass9">#endif<br/>
</span>
</DIV>
...このサンプルではプロファイルおよびカバレッジの測定結果を両方とも出力していますが、どちらか片方のみ出力させることも可能です。その場合は出力させたくないほうのライターとして NULL を指定してください。
        </P>
        <P>
            尚、マルチスレッドの場合はスレッド毎に定義する必要があります。マルチスレッドでのプロファイラの使い方は基本的にロガーと同じですので *_logger と *_profiler という名称の違いはありますが、 <A href="#step3">.tsv形式ログ出力＆マルチスレッドサンプル</A> を参考してください。
        </P>


## リファレンス

- <A class="bar" href="#statements">ステートメントハックによってマクロ置換されるステートメント</A>
- <A class="bar" href="#macros">マクロ</A>
- <A class="bar" href="#namespace">名前空間</A>
- <A class="bar" href="#types">型</A>
- <A class="bar" href="#functions">関数</A>
- <A class="bar" href="#profile-columns">プロファイルデータの項目</A>
            
<A name="statements"></A>
### ステートメントハックによってマクロ置換されるステートメント

<TABLE class="list">
<TR><TH class="header"><NOBR>ステートメント</NOBR></TH><TH class="header">スコープ</TH><TH class="header">補足</TH></TR>
<TR><TD>if</TD><TD class="OK"><NOBR>形成する</NOBR></TD><TD>if ステートメントの条件判定結果(bool値)もログに出力します。</TD></TR>
<TR class="check"><TD>while</TD><TD class="NG"><NOBR>形成しない</NOBR></TD><TD>while ステートメントの条件判定結果(bool値)もログに出力します。</TD></TR>
<TR><TD>switch</TD><TD class="OK"><NOBR>形成する</NOBR></TD><TD>switch ステートメントの条件判定結果(int値)もログに出力します。</TD></TR>
<TR class="check"><TD>goto</TD><TD class="NG"><NOBR>形成しない</NOBR></TD><TD></TD></TR>
<TR><TD>break</TD><TD class="NG"><NOBR>形成しない</NOBR></TD><TD></TD></TR>
<TR class="check"><TD>continue</TD><TD class="NG"><NOBR>形成しない</NOBR></TD><TD></TD></TR>
<TR><TD>return</TD><TD class="NG"><NOBR>形成しない</NOBR></TD><TD>『return func();』のような形の場合、極力『func()』の呼び出しが終了した時点でログを出力するようにしていますが、コンパイラ及びのバージョン等によっては必ずしもはそうなっていないので注意してください。</TD></TR>
<TR class="check"><TD>do</TD><TD class="OK"><NOBR>形成する</NOBR></TD><TD></TD></TR>
<TR><TD>for</TD><TD class="OK"><NOBR>形成する</NOBR></TD><TD></TD></TR>
<TR class="check"><TD>try</TD><TD class="OK"><NOBR>形成する</NOBR></TD><TD></TD></TR>
<TR><TD>throw</TD><TD class="OK"><NOBR>形成する</NOBR></TD><TD>『throw func();』のような形の場合、極力『func()』の呼び出しが終了した時点でログを出力するようにしていますが、コンパイラ及びのバージョン等によっては必ずしもはそうなっていないので注意してください。</TD></TR>
<TR class="check"><TD>new</TD><TD class="OK"><NOBR>形成する</NOBR></TD><TD></TD></TR>
<TR><TD>delete</TD><TD class="OK"><NOBR>形成する</NOBR></TD><TD></TD></TR>
</TABLE>
    
<A name="macros"></A>
### マクロ

<A name="direction-macros"></A>
#### 指示マクロ

<TABLE class="list">
<TR><TH class="header">マクロ</TH><TH class="header">説明</TH></TR>
<TR><TD>BUG_DISABLE_BUGBEARD</TD><TD>このマクロが定義されいる場合、バグベアードはロードされず、<A href="#evil-contract">"悪魔の契約"</A>も不要です。</TD></TR>
<TR class="check"><TD>BUG_EVIL_CONTRACT</TD><TD>バグベアードを利用するには<A href="#evil-contract">"悪魔の契約"</A>をよく読んでその意味を理解した上でこのマクロを定義してください。</TD></TR>
<TR><TD>BUG_STATEMENT_HACK</TD><TD>バグベアードの真骨頂であるステートメントハックを有効にするにはこのマクロを定義した上で bug.h をインクルードしてください。逆に一度有効にしたステートメントハックをソースコードの途中から無効したい場合はこのマクロの定義を解除(#undef)した上で再度 bug.h をインクルードしてください。<BR>cf. <A href="#statements">ステートメントハックによってマクロ置換されるステートメント</A></TD></TR>
<TR class="check"><TD>BUG_USE_CHAR</TD><TD>char型をバグベアードで使用する文字型として指定する場合にこのマクロを定義してください。このマクロも BUG_USE_WCHAR もともに定義されていない場合で且つ、UNICODE マクロおよび _UNICODE マクロが定義されていない場合、このマクロは自動で定義されます。</TD></TR>
<TR><TD>BUG_USE_WCHAR</TD><TD>wchar_t型をバグベアードで使用する文字型として指定する場合にこのマクロを定義してください。このマクロも BUG_USE_CHAR もともに定義されていない場合で且つ、UNICODE マクロもしくは _UNICODE マクロが定義されていた場合、このマクロは自動で定義されます。</TD></TR>
<TR class="check"><TD>BUG_SINGLE_PROCESS</TD><TD>シングルプロセスで動作するプログラム上でバグベアードを利用する場合、このマクロを定義してください。このマクロも BUG_MULTI_PROCESS マクロもともに定義されていない場合、このマクロは自動で定義されます。</TD></TR>
<TR><TD>BUG_MULTI_PROCESS</TD><TD>マルチプロセスで動作するプログラム上でバグベアードを利用する場合、このマクロを定義してください。</TD></TR>
<TR class="check"><TD>BUG_SINGLE_THREAD</TD><TD>シングルスレッドで動作するプログラム上でバグベアードを利用する場合、このマクロを定義してください。このマクロも BUG_MULTI_THREAD マクロもとも定義されていない場合で且つ、_MT マクロおよび __MT__ マクロが定義されていない場合、このマクロは自動で定義されます。</TD></TR>
<TR><TD>BUG_MULTI_THREAD</TD><TD>マルチスレッドで動作するプログラム上でバグベアードでバグベアードを利用する場合、このマクロを定義してください。このマクロも、BUG_SINGLE_THREAD マクロも定義されていない場合で且つ、_MT マクロもしくは __MT__ マクロが定義されていた場合、このマクロは自動で定義されます。</TD></TR>
<TR class="check"><TD>BUG_THREAD_LOCAL_STORAGE</TD><TD>バグベアードに処理系由来のスレッドローカルストレージ機能を使用させる場合、このマクロでスレッドローカルストレージであることを示す為の型への修飾を指定してください。指定例は bug.h 内のコメントを参照してください。</TD></TR>
<TR><TD>BUG_WITHOUT_LOCATION_INFO</TD><TD>このマクロが定義されているとロケーション情報(__FILE__,__LINE__,及び関数名)をログ出力しません。</TD></TR>
<TR class="check"><TD>BUG_MASK_SOURCECODE</TD><TD>このマクロが定義されているとステートメントハックによるログ出力中の条件式が "..." に置き換えられます。</TD></TR>
<TR><TD>BUG_FUNCTION_NAME</TD><TD>__function__ のような関数名を取得する組み込みマクロを利用できる処理系で、関数名をログに出力させた場合にこのマクロでその処理系が持つ関数名取得用組み込みマクロを指定してください。このマクロが定義されていない場合でも処理系によってはこのマクロは自動で定義されます。</TD></TR>
<TR class="check"><TD>BUG_NO_FUNCTION_NAME</TD><TD>BUG_FUNCTION_NAME マクロが自動で定義される処理系で、関数名をログに出力させたく場合はこのマクロを定義することで BUG_FUNCTION_NAME マクロの自動定義を抑止できます。</TD></TR>
<TR><TD>BUG_DISABLED_PSAPI</TD><TD>Windows で利用する際にお使いのコンパイル環境で PSAPI が利用できない場合は、このマクロを定義してください。このマクロが定義されると bug_enum_module_version_info() の実装が抑止されます。</TD></TR>
<TR class="check"><TD>BUG_DEFINE_GLOBAL_LOGGER</TD><TD>このマクロはシンタックスシュガー的なもので、このマクロでグローバルなロガーの定義を指定おくとバグベアードのヘッダーファイル内でロガーの定義が行われます。このマクロを利用することでロガーを定義する際にバグベアードのヘッダーファイルを２度インクルードすることを回避できます。使用例は <A href="#step5">プロファイル＆カバレッジ測定サンプル</A> を参照してください。</TD></TR>
<TR><TD>BUG_DEFINE_GLOBAL_PROFILER</TD><TD>このマクロはシンタックスシュガー的なもので、このマクロでグローバルなプロファイラの定義を指定おくとバグベアードのヘッダーファイル内でプロファイラの定義が行われます。このマクロを利用することでプロファイラを定義する際にバグベアードのヘッダーファイルを２度インクルードすることを回避できます。使用例は <A href="#step5">プロファイル＆カバレッジ測定サンプル</A> を参照してください。</TD></TR>
<TR class="check"><TD>BUG_WITHOUT_TSV_LOG_HEADER</TD><TD>このマクロが定義されていると .tsv ログのヘッダー行を出力しなくなります。</TD></TR>
<TR><TD>BUG_WITHOUT_TSV_PROFILE_HEADER</TD><TD>このマクロが定義されていると .tsv プロファイルデータのヘッダー行を出力しなくなります。</TD></TR>
<TR class="check"><TD>BUG_WITHOUT_TSV_COVERAGE_HEADER</TD><TD>このマクロが定義されていると .tsv カバレッジデータのヘッダー行を出力しなくなります。</TD></TR>
<!--TR><TD>BUG_LANG_JP</TD><TD></TD></TR>
<TR class="check"><TD>BUG_LANG_EN</TD><TD></TD></TR>
<TR><TD>BUG_DISABLED_WHILE_SCOPE</TD><TD></TD></TR>
<TR class="check"><TD>BUG_DISABLED_SWITCH_SCOPE</TD><TD></TD></TR>
<TR><TD>BUG_DISABLED_THROW_SCOPE</TD><TD></TD></TR>
<TR class="check"><TD>BUG_NEED_WHILE_CAST</TD><TD></TD></TR-->
</TABLE>

<A name="flag-macros"></A>
#### フラグマクロ

<TABLE class="list">
<TR><TH class="header">マクロ</TH><TH class="header">説明</TH></TR>
<TR><TD>BUGBEARD_BUG_H</TD><TD>bug.h の所謂インクルードガードに相当するマクロです。ただし、一般的なインクルードガードはそのヘッダファイル全体が多重に展開されることを防ぐ作りなっていますが、bug.h は BUG_STATEMENT_HACK マクロの定義状態を変更しながら複数回インクルードされること想定した作りとなっており、ステートメントハック関連のマクロ定義/解除がインクルードガードの対象になっていません。</TD></TR>
<TR class="check"><TD>BUG_LOAD_BUGBEARD</TD><TD>BUG_DISABLE_BUGBEARD マクロが定義されずに bug.h がインクルードされたことにより、バグベアードがロードされている場合に定義されます。BUG_* な命名のマクロは全てバグベアードがロードされていない時にはきえさりますが、その他のコードでバグベアードがロードされていない時に消し去りたい場合はそのコードを #if defined(BUG_LOAD_BUGBEARD) ～ #endif で囲んでください。</TD></TR>
<TR><TD>BUG_MS_WINDOWS</TD><TD>Windows環境でバグベアードがロードされている場合に定義されます。</TD></TR>
</TABLE>

<A name="function-macros"></A>
#### 機能マクロ

<TABLE class="list">
<TR><TH class="header">マクロ</TH><TH class="header">説明</TH></TR>
<TR><TD>BUG_define_logger</TD><TD>ロガーを定義するのに使用します。マルチスレッドの場合、各スレッド毎に定義する必要があります。</TD></TR>
<TR class="check">
    <TD>BUG_puts</TD>
    <TD>指定されたテキストをログ出力します。このマクロは標準関数の puts と同じくただ与えられた文字列を出力するだけで printf のような書式機能はありません。書式を利用したい場合は BUG_FORM を利用してください。
        <DIV class="sample">
        <span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_puts</span><span class="SpanClass10">(</span><span class="SpanClass6">"このロリコンどもめ！"</span><span class="SpanClass10">);</span>
        </DIV>        
    </TD>
</TR>
<TR>
    <TD>BUG_VAL</TD>
    <TD>
        指定された変数・オブジェクトの内容をその名前とともに文字列に変換します。BUG_puts マクロと組み合わせて変数・オブジェクトをログ出力するのに使用します。
        <DIV class="sample">
        <span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_puts</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_VAL</span><span class="SpanClass10">(</span><span class="SpanClass11">speech</span><span class="SpanClass10">));</span>
        </DIV>        
    </TD>
</TR>
<TR class="check">
    <TD>BUG_FORM</TD>
    <TD>
        printfと同様の引数をとり、文字列を返します。
        <DIV class="sample">
        <span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_puts</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_FORM</span><span class="SpanClass10">(</span><span class="SpanClass6">"%s"</span><span class="SpanClass10">,</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass6">"このロリコンどもめ！"</span><span class="SpanClass10">));</span>
        </DIV>        
    </TD>
</TR>
<TR><TD>BUG_exec</TD><TD>バグベアードがロードされている場合にのみ引数部のコードが有効になります。</TD></TR>
<TR class="check"><TD>BUG_scope</TD><TD>指定されたテキストをスコープログ出力します。</TD></TR>
<TR>
    <TD>BUG_CHAR_TYPE</TD>
    <TD>
        バグベアード使用される文字型を示します。Windows プログラミングでの TCHAR に相当し、BUG_USE_CHAR マクロが定義されていれば char 型を BUG_USE_WCHAR マクロが定義されていれば wchar_t 型を示します。
        <DIV class="sample">
        <span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass16">const</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">BUG_CHAR_TYPE</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">*</span><span class="SpanClass11">speech</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass10">=</span><span class="SpanClass0">&nbsp;</span><span class="SpanClass11">BUG_T</span><span class="SpanClass10">(</span><span class="SpanClass6">"このロリコンどもめ！"</span><span class="SpanClass10">);</span>
        </DIV>        
    </TD>
</TR>
<TR class="check"><TD>BUG_API_T</TD><TD>BUG_USE_CHAR/BUG_USE_WCHAR マクロにあわせて Windows API を修飾し ANSI 版と UNICODE 版の切り替えを用意にします。</TD></TR>
<TR>
    <TD>BUG_T</TD>
    <TD>
        BUG_USE_CHAR/BUG_USE_WCHAR マクロにあわせて文字および文字列の型を修飾します。このマクロは Windows プログラミングでの _T/TEXT マクロに相当します。
        <DIV class="sample">
        <span class="SpanClass0">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="SpanClass11">BUG_puts</span><span class="SpanClass10">(</span><span class="SpanClass11">BUG_T</span><span class="SpanClass10">(</span><span class="SpanClass6">"たまにはロリコンもいいよね！"</span><span class="SpanClass10">));</span>
        </DIV>
    </TD>
</TR>
<TR class="check"><TD>BUG_LOG</TD><TD>カレントスレッドに関連づけられているロガーを取得します。</TD></TR>
<TR><TD>BUG_MSG</TD><TD>ログ出力される元テキストにロケーション情報を付加します。ユーザプログラミングにおいてこのマクロは通常意識する必要はありません。</TD></TR>
<TR class="check"><TD>BUG_COMPILER_NAME</TD><TD>コンパイルに使用したコンパイラの名前です。</TD></TR>
<TR><TD>BUG_COMPILER_VERSION_NUMBER</TD><TD>コンパイルに使用したコンパイラのバージョン番号(数値)です。</TD></TR>
<TR class="check"><TD>BUG_COMPILER_VERSION</TD><TD>コンパイルに使用したコンパイラのバージョン情報(文字列)です。</TD></TR>
<!--TR><TD>BUG_FORM_I64</TD><TD></TD></TR>
<TR class="check"><TD>BUG_NOTHING</TD><TD></TD></TR>
<TR><TD>BUG_T_CORE</TD><TD></TD></TR>
<TR class="check"><TD>BUG_ID</TD><TD></TD></TR>
<TR><TD>BUG_ID_core</TD><TD></TD></TR>
<TR class="check"><TD>BUG_TO_STRING</TD><TD></TD></TR>
<TR><TD>BUG_TO_STRING_CORE</TD><TD></TD></TR-->
</TABLE>

<A name="namespace"></A>
### 名前空間

<TABLE class="list">
<TR><TH class="header">namespace</TH><TH class="header">説明</TH></TR>
<TR><TD>bugbeard</TD><TD>バグベアードの各種型や関数等は一部の例外を除き全てこの名前空間で定義されます。</TD></TR>
<TR class="check"><TD>bugbeard::bug_term</TD><TD>バグベアードで使用される文字列定数(全てではない)がこの名前空間で定義されます。</TD></TR>
</TABLE>

<A name="types"></A>
### 型

<A name="typedef"></A>
#### typedef

<TABLE class="list">
<TR><TH class="header">型</TH><TH class="header">定義</TH><TH class="header">説明</TH></TR>
<TR><TD>bug_char</TD><TD>BUG_CHAR_TYPE</TD><TD>バグベアードで使用される文字型です。</TD></TR>
<TR class="check"><TD>bug_string</TD><TD>std::basic_string&lt;bug_char&gt;</TD><TD>バグベアードで使用される文字列型です。</TD></TR>
<TR><TD>bug_form</TD><TD>bug_form_ex&lt;&gt;</TD><TD>printf書式で文字列を作成するのに使用されるクラスです。BUG_FORM マクロはこのクラスに置換されます。</TD></TR>
<TR class="check"><TD>bug_sint64_type</TD><TD>int64_t</TD><TD>バグベアードで使用される int64_t 。stdint.h を持たない VC++ の為に存在します。</TD></TR>
<TR><TD>bug_uint64_type</TD><TD>uint64_t</TD><TD>バグベアードで使用される uint64_t 。stdint.h を持たない VC++ の為に存在します。</TD></TR>
<!--TR><TD>bug_default_stamp</TD><TD></TD><TD></TD></TR-->
</TABLE>

<A name="class"></A>
#### class

<H5>utilities</H5>
<TABLE class="list">
<TR><TH class="header">クラス名</TH><TH class="header">説明</TH></TR>
<TR><TD>bug_form_ex</TD><TD>printf書式による文字列作成機能を提供します。</TD></TR>
<TR class="check"><TD>bug_clock</TD><TD>現在時刻情報を提供します。</TD></TR>
<TR><TD>bug_dull_dir</TD><TD>bug_dirの無能版(ディレクトリを作成しない)。</TD></TR>
<TR class="check"><TD>bug_dir</TD><TD>ファイルパス文字列の構築とともにディレクトリ作成を行うユーティリティクラス。</TD></TR>
<TR><TD>bug_mutex</TD><TD>汎用ミューテックスクラス。</TD></TR>
<TR class="check"><TD>bug_lock</TD><TD>自動ロッククラス。</TD></TR>
<TR><TD>bug_smart_ptr_ref_cnt</TD><TD>内包用リファレンスカウンタ。</TD></TR>
<TR class="check"><TD>bug_smart_ptr_share</TD><TD>外付け用リファレンスカウンタ。</TD></TR>
<TR><TD>bug_smart_ptr</TD><TD>スマートポインタ。</TD></TR>
<TR class="check"><TD>bug_thread_local_storage</TD><TD>スレッドローカルストレージ。</TD></TR>
<TR><TD>bug_OSVERSIONINFO</TD><TD>Windowsバージョン情報クラス。</TD></TR>
<!--TR><TD>bug_thread_local_storage_base</TD><TD></TD></TR-->
</TABLE>

<H5>writer</H5>
このクラス群はバグベアードによるログの出力先を指定するのに使用されます。
<TABLE class="list">
<TR><TH class="header">クラス名</TH><TH class="header">説明</TH></TR>
<TR><TD>bug_writer</TD><TD>ライター基本クラス。このクラスはインターフェイスを提供する為の抽象クラスなので直接は利用できません。</TD></TR>
<TR class="check"><TD>bug_file_writer_base</TD><TD>指定されたファイルポインタ(FILE*)に対して書き込みを行うライター。</TD></TR>
<TR><TD>bug_file_writer</TD><TD>指定されたファイルパスに対して書き込みを行うライター。Windows 環境下では bug_handle_writer の派生型として実装され、その他の環境下では bug_file_writer_base の派生型として実装されます。なお、Windows環境では UNICODE/_UNICODE マクロや BUG_USE_CHAR/BUG_USE_WCHAR マクロに関係なく常に MBCS および UNICODE でファイルパスを指定できます。</TD></TR>
<TR class="check"><TD>bug_stream_writer</TD><TD>指定されたストリーム(std::otream)に対して書き込みを行うライター。</TD></TR>
<TR><TD>bug_fstream_writer</TD><TD>指定されたファイルパスに対して書き込みを行うライター。bug_file_writerとは異なり名前の通り std::ofstream ベースの実装。</TD></TR>
<TR class="check"><TD>bug_handle_writer</TD><TD>指定されたハンドルに対して書き込みを行うライター。Windows専用。</TD></TR>
<TR><TD>bug_OutputDebugString_writer</TD><TD>OutputDebugString()を利用するライター。Windows専用。</TD></TR>
</TABLE>

<H5>stamp</H5>
このクラス群はバグベアードによるログ中のタイムスタンプの種類・形式を指定するのに使用されます。
<TABLE class="list">
<TR><TH class="header">クラス名</TH><TH class="header">説明</TH></TR>
<TR><TD>bug_stamp</TD><TD>タイムスタンプ基本クラス。このクラスはインターフェイスを提供する為の抽象クラスなので直接は利用できません。</TD></TR>
<TR class="check"><TD>bug_counter_stamp</TD><TD>カウンタ型タイムスタンプ。形式：%d</TD></TR>
<TR><TD>bug_hex_counter_stamp</TD><TD>16進表記のカウンタ型タイムスタンプ。形式：0x%08.8X</TD></TR>
<TR class="check"><TD>bug_clock_stamp</TD><TD>時刻型タイムスタンプ。形式：%2.2d:%2.2d:%2.2d</TD></TR>
<TR><TD>bug_clock_stamp_with_date</TD><TD>日付付き時刻型タイムスタンプ。形式：%4.4d-%2.2d-%2.2d(%s) %2.2d:%2.2d:%2.2d</TD></TR>
<TR class="check"><TD>bug_short_clock_stamp</TD><TD>ショート時刻型タイムスタンプ。形式：%2.2d%2.2d%2.2d</TD></TR>
<TR><TD>bug_short_clock_stamp_with_date</TD><TD>日付付きショート時刻型タイムスタンプ。形式：%4.4d%2.2d%2.2d%2.2:%2.2d%2.2d</TD></TR>
<TR class="check"><TD>bug_clock_stamp_ex</TD><TD>精細時刻型タイムスタンプ。形式：%2.2d:%2.2d:%2.2d.%3.3d</TD></TR>
<TR><TD>bug_clock_stamp_ex_with_date</TD><TD>日付付き精細時刻型タイムスタンプ。形式：%4.4d-%2.2d-%2.2d(%s) %2.2d:%2.2d:%2.2d.%3.3d</TD></TR>
<TR class="check"><TD>bug_clock_stamp_ex2</TD><TD>高精細時刻型タイムスタンプ。形式：%2.2d:%2.2d:%2.2d.%6.6d</TD></TR>
<TR><TD>bug_clock_stamp_ex2_with_date</TD><TD>日付付き高精細時刻型タイムスタンプ。形式：%4.4d-%2.2d-%2.2d(%s) %2.2d:%2.2d:%2.2d.%6.6d</TD></TR>
<TR class="check"><TD>bug_GetTickCount_stamp</TD><TD>GetTickCount型タイムスタンプ。Windows専用。形式：%08.8X</TD></TR>
<TR><TD>bug_QueryPerformanceCounter_stamp</TD><TD>QueryPerformanceCounter型タイムスタンプ(RAW)。Windows専用。形式：%08.8X%08.8X</TD></TR>
<TR class="check"><TD>bug_QueryPerformanceSecond_stamp</TD><TD>QueryPerformanceCounter型タイムスタンプ(秒＋マイクロ秒)。Windows専用。形式：%7d.%06.6d</TD></TR>
</TABLE>

<H5>message</H5>
<TABLE class="list">
<TR><TH class="header">クラス名</TH><TH class="header">説明</TH></TR>
<TR><TD>bug_message</TD><TD>ロケーション情報(__FILE__ 及び __LINE__)とログ出力するテキストを保持します。</TD></TR>
</TABLE>

<H5>profile time</H5>
<TABLE class="list">
<TR><TH class="header">クラス名</TH><TH class="header">説明</TH></TR>
<TR><TD>bug_profile_time_type</TD><TD>高精度時間型。</TD></TR>
<TR class="check"><TD>bug_profile_time_set</TD><TD>bug_profile_time_type で、稼働時間、バグ時間、実働時間を保持します。</TD></TR>
<TR><TD>bug_profile_time_score</TD><TD>bug_profile_time_set で、自スコープと子スコープの時間を保持します。</TD></TR>
<TR class="check"><TD>bug_profile_time_score_set</TD><TD>特定のスコープに関する全プロファイルデータを保持します。</TD></TR>
<TR><TD>bug_bug_time_scope</TD><TD>その生存期間でバグベアードによるオーバーヘッド(バグ時間)を測定します。</TD></TR>
<TR class="check"><TD>bug_profile_scope</TD><TD>その生存期間でスコープの稼働時間を測定します。</TD></TR>
</TABLE>

<H5>logger</H5>
<TABLE class="list">
<TR><TH class="header">クラス名</TH><TH class="header">説明</TH></TR>
<TR><TD>bug_logger</TD><TD>ロガー基本クラス。このクラスは主にインターフェイスを提供する為の抽象クラスなので直接は利用できません。</TD></TR>
<TR class="check"><TD>bug_tsv_logger</TD><TD>.tsv(タブ区切り)形式のログを出力します。</TD></TR>
<TR><TD>bug_tree_logger</TD><TD>ツリー形式のログを出力します。</TD></TR>
<TR class="check"><TD>bug_compact_tree_logger</TD><TD>圧縮ツリー形式のログを出力します。ツリー部分が bug_tree_logger の約1/6に圧縮されます。</TD></TR>
</TABLE>

<H5>profiler</H5>
<TABLE class="list">
<TR><TH class="header">クラス名</TH><TH class="header">説明</TH></TR>
<TR><TD>bug_profiler</TD><TD>プロファイラー基本クラス。このクラスはプロファイルデータを保持しますが、出力する機能を持ち合わせいないので直接指定しても意味がありません。このクラスの代わりに bug_tsv_profiler を指定してください。</TD></TR>
<TR class="check"><TD>bug_tsv_profiler</TD><TD>.tsv(タブ区切り)形式でプロファイルおよびカバレッジ測定結果を出力します。</TD></TR>
</TABLE>

<!--
#### element
bug_dummy_if
bug_element
bug_scope
bug_scope_out
bug_new_core
bug_if_core
bug_while_core
bug_switch_core
-->

<!--
<A name="const"></A>
### 定数
empty
horizon_line
level_line
level_branch
level_up
level_down
begin_prefix
end_prefix
session_root
location_format
unknown_location
dir_separator
return_code
wday_names
stamp_title
-->

<A name="functions"></A>
### 関数

<TABLE class="list">
<TR><TH class="header">関数名</TH><TH class="header">説明</TH></TR>
<TR><TD>bug_binary_prefix</TD><TD>符号なし64ビット値を<A href="http://ja.wikipedia.org/wiki/二進接頭辞" >二進接頭辞</A>で修飾した文字列(bug_string型)に変換します。bug_binary_prefix(39029211136, BUG_T("Byte")) で呼び出すと "36.3GiByte(39029211136)" のような文字列が返ります。第二引数は省略可。</TD></TR>
<TR class="check"><TD>bug_hex_encode</TD><TD>与えられたバイナリデータをHEXエンコードされた文字列(bug_string型)に変換します。</TD></TR>
<TR><TD>bug_encode_value</TD><TD>各種データを文字列(bug_string型)に変換します。BUG_VALマクロで呼び出される bug_encode() はこの bug_encode_value() を利用して各種データを文字列に変換します。その他なデータ型は bug_hex_encode() で HEX エンコードされます。独自のデータ型を HEX エンコード以外の形でログに残したい場合は自前でこの bug_encode_value() のオーバーロードを定義してください。</TD></TR>
<TR class="check"><TD>bug_encode</TD><TD>BUG_VALマクロ用の本体関数で、BUG_VALマクロで指定された変数の「名前」、「アドレス」、「内容」をひとつの文字列(bug_string型)にまとめます。</TD></TR>
<TR><TD>bug_run_string</TD><TD>第一引数で指定された数だけ第二引数で指定された文字列を繰り返した文字列(bug_string型)を返します。</TD></TR>
<TR class="check"><TD>bug_get_win32_err_msgA</TD><TD>Win32APIのエラーコード(GetLastError())に対応するエラーメッセージ(std::string型)を返します。Windows専用。</TD></TR>
<TR><TD>bug_get_win32_err_msgW</TD><TD>Win32APIのエラーコード(GetLastError())に対応するエラーメッセージ(std::wstring型)を返します。Windows専用。</TD></TR>
<TR class="check"><TD>bug_get_winver</TD><TD>Windows のバージョン＋エディション表記(bug_string型)を返します。Windows専用。<BR>ex. "Microsoft Windows Vista Business Edition, 32-bit"</TD></TR>
<TR><TD>bug_compile_info</TD><TD>コンパイルを行った日時、コンパイルに使用したコンパイラの名称およびバージョンを第一引数で指定されたロガーを使って出力します。</TD></TR>
<TR class="check"><TD>bug_arg_info</TD><TD>main()関数の引数の内容を第一引数で指定されたロガーを使って出力します。</TD></TR>
<TR><TD>bug_windows_version_info</TD><TD>Windowsのバージョン情報を第一引数で指定されたロガーを使って出力します。Windows専用。</TD></TR>
<TR class="check"><TD>bug_module_version_info</TD><TD>第二引数で指定された実行形式ファイル(*.exe;*.dll)のバージョン情報を第一引数で指定されたロガーを使って出力します。Windows専用。</TD></TR>
<TR><TD>bug_enum_module_version_info</TD><TD>カレントプロセスがロードしている全てのモジュール(*.exe;*.dll)のバージョン情報を第一引数で指定されたロガーを使って出力します。Windows専用。</TD></TR>
<TR class="check"><TD>bug_memory_info</TD><TD>システム全体のメモリの使用状況を第一引数で指定されたロガーを使って出力します。Windows専用。</TD></TR>
<TR><TD>bug_drive_info</TD><TD>第二引数で指定されたドライブの情報を第一引数で指定されたロガーを使って出力します。Windows専用。</TD></TR>
<TR class="check"><TD>bug_enum_drive_info</TD><TD>全てのドライブの情報を第一引数で指定されたロガーを使って出力します。Windows専用。</TD></TR>
<TR><TD>bug_MonitorEnumProc</TD><TD>第二引数で指定されたモニターの情報を第一引数で指定されたロガーを使って出力します。Windows専用。</TD></TR>
<TR class="check"><TD>bug_enum_monitor_info</TD><TD>全てのモニターの情報を第一引数で指定されたロガーを使って出力します。Windows専用。</TD></TR>
<TR><TD>bug_enum_display_info</TD><TD>全てのディスプレイの情報を第一引数で指定されたロガーを使って出力します。Windows専用。</TD></TR>
<TR class="check"><TD>bug_env</TD><TD>第二引数で指定された環境変数の内容を第一引数で指定されたロガーを使って出力します。Windows専用。</TD></TR>
<TR><TD>bug_enum_env</TD><TD>全ての環境変数の内容を第一引数で指定されたロガーを使って出力します。Windows専用。</TD></TR>
<TR class="check"><TD>bug_windows_system_info</TD><TD>Win32APIの GetSystemInfo() で得られた情報を第一引数で指定されたロガーを使って出力します。Windows専用。</TD></TR>
<TR><TD>bug_file_hash</TD><TD>第二引数で指定されたファイルのハッシュ値を第一引数で指定されたロガーを使って出力します。デフォルトではMD5が使用されますが第三引数＋第四引数でその他のハッシュ関数も指定できます。Windows専用。</TD></TR>
<TR class="check"><TD>bug_enum_module_hash</TD><TD>カレントプロセスがロードしている全てのモジュール(*.exe;*.dll)のハッシュ値を第一引数で指定されたロガーを使って出力します。Windows専用。</TD></TR>
<!--TR class="check"><TD>get_bug_smart_by_target</TD><TD></TD></TR>
<TR><TD>get_target_by_bug_smart</TD><TD></TD></TR-->
</TABLE>

<A name="profile-columns"></A>
### プロファイルデータの項目

<TABLE class="list">
<TR><TH class="header">項目名</TH><TH class="header">説明</TH></TR>
<TR><TD>プロセスID</TD><TD>プロセスID。BUG_MULTI_PROCESS マクロが定義されている場合にのみ出力されます。</TD></TR>
<TR class="check"><TD>スレッドID</TD><TD>スレッドID。BUG_MULTI_THREAD マクロが定義されている場合にのみ出力されます。</TD></TR>
<TR><TD>__FILE__</TD><TD>ファイル名。オーバーオールスコープでは "@OVERALL_SCOPE" となります。</TD></TR>
<TR class="check"><TD>__LINE__</TD><TD>行番号。オーバーオールスコープでは 0 となります。</TD></TR>
<TR><TD>__function__</TD><TD>関数名。BUG_FUNCTION_NAME マクロが定義されている場合にのみ出力されます。オーバーオールスコープでは "@OVERALL_SCOPE" となります。</TD></TR>
<TR class="check"><TD>スコープ</TD><TD>スコープ。オーバーオールスコープでは "@OVERALL_SCOPE" となります。</TD></TR>
<TR><TD><NOBR>合計総稼働時間</NOBR></TD><TD>そのスコープ自身とその内包するスコープの実行に要した全ての時間の合計。合計総稼働時間＝(合計総バグ時間＋合計総実働時間)＝(合計自稼働時間＋合計子稼働時間)＝SUM(総稼働時間)。</TD></TR>
<TR class="check"><TD>合計総バグ時間</TD><TD>そのスコープ自身とその内包するスコープの測定の為に要した全てのオーバーヘッドの合計。合計総バグ時間＝(合計自バグ時間＋合計子バグ時間)＝SUM(総バグ時間)。</TD></TR>
<TR><TD>合計総実働時間</TD><TD>そのスコープ自身とその内包するスコープの実行に要した全ての時間から測定の為のオーバーヘッドを差し引いた時間の合計。合計総実働時間＝(合計自実働時間＋合計子実働時間)＝SUM(総実働時間)。</TD></TR>
<TR class="check"><TD>合計自稼働時間</TD><TD>そのスコープ自身の実行に要した全ての時間の合計(内包するスコープの時間は除く)。合計自稼働時間＝(合計自バグ時間＋合計自実働時間)＝SUM(自実働時間)。</TD></TR>
<TR><TD>合計自バグ時間</TD><TD>そのスコープ自身の測定の為に要した全ての時間の合計(内包するスコープの時間は除く)。合計自バグ時間＝SUM(自バグ時間)。</TD></TR>
<TR class="check"><TD>合計自実働時間</TD><TD>そのスコープ自身の実行に要した全ての時間から測定の為のオーバーヘッドを差し引いた時間の合計(内包するスコープの時間は除く)。合計自実働時間＝SUM(自実働時間)。</TD></TR>
<TR><TD>合計子稼働時間</TD><TD>その内包するスコープの実行に要した全ての時間の合計。合計子稼働時間＝(合計子バグ時間＋合計子実働時間)＝SUM(子実働時間)。</TD></TR>
<TR class="check"><TD>合計子バグ時間</TD><TD>その内包するスコープの測定の為に要した全ての時間の合計。合計子バグ時間＝SUM(子バグ時間)。</TD></TR>
<TR><TD>合計子実働時間</TD><TD>その内包するスコープの実行に要した全ての時間から測定の為のオーバーヘッドを差し引いた時間の合計。合計子実働時間＝SUM(子実働時間)。</TD></TR>
<TR class="check"><TD>コールカウント</TD><TD>そのスコープが実行された回数。</TD></TR>
<TR><TD>平均総稼働時間</TD><TD>そのスコープ自身とその内包するスコープの実行に要した全ての時間の平均。平均総稼働時間＝(合計総稼働時間÷コールカウント)＝(平均総バグ時間＋平均総実働時間)＝(平均自稼働時間＋平均子稼働時間)</TD></TR>
<TR class="check"><TD>平均総バグ時間</TD><TD>そのスコープ自身とその内包するスコープの測定の為に要した全てのオーバーヘッドの平均。平均総バグ時間＝(合計総バグ時間÷コールカウント)＝(平均自バグ時間＋平均子バグ時間)。</TD></TR>
<TR><TD>平均総実働時間</TD><TD>そのスコープ自身とその内包するスコープの実行に要した全ての時間から測定の為のオーバーヘッドを差し引いた時間の平均。平均総実働時間＝(合計総実働時間÷コールカウント)＝(平均自実働時間＋平均子実働時間)。</TD></TR>
<TR class="check"><TD>平均自稼働時間</TD><TD>そのスコープ自身の実行に要した全ての時間の平均(内包するスコープの時間は除く)。平均自稼働時間＝(合計自稼働時間÷コールカウント)＝(平均自バグ時間＋平均自実働時間)。</TD></TR>
<TR><TD>平均自バグ時間</TD><TD>そのスコープ自身の測定の為に要した全ての時間の平均(内包するスコープの時間は除く)。平均自バグ時間＝(合計自バグ時間÷コールカウント)。</TD></TR>
<TR class="check"><TD>平均自実働時間</TD><TD>その内包するスコープの実行に要した全ての時間の平均。平均子稼働時間＝(合計子稼働時間÷コールカウント)＝(平均子バグ時間＋平均子実働時間)。</TD></TR>
<TR><TD>平均子稼働時間</TD><TD>その内包するスコープの実行に要した全ての時間の平均。平均子稼働時間＝(合計子稼働時間÷コールカウント)＝(平均子バグ時間＋平均子実働時間)。</TD></TR>
<TR class="check"><TD>平均子バグ時間</TD><TD>その内包するスコープの測定の為に要した全ての時間の平均。平均子バグ時間＝(合計子バグ時間÷コールカウント)。</TD></TR>
<TR><TD>平均子実働時間</TD><TD>その内包するスコープの実行に要した全ての時間から測定の為のオーバーヘッドを差し引いた時間の平均。平均子実働時間＝(合計子実働時間÷コールカウント)。</TD></TR>
<TR class="check"><TD>最小スタンプ</TD><TD>総実働時間が最小となった時のそのスコープのロガー上でのスタンプ。</TD></TR>
<TR><TD>最小総稼働時間</TD><TD>総実働時間が最小となった時のそのスコープ自身とその内包するスコープの実行に要した全ての時間。最小総稼働時間＝(最小総バグ時間＋最小総実働時間)＝(最小自稼働時間＋最小子稼働時間)</TD></TR>
<TR class="check"><TD>最小総バグ時間</TD><TD>総実働時間が最小となった時のそのスコープ自身とその内包するスコープの測定の為に要した全てのオーバーヘッド。最小総バグ時間＝(最小自バグ時間＋最小子バグ時間)。</TD></TR>
<TR><TD>最小総実働時間</TD><TD>そのスコープ自身とその内包するスコープの実行に要した全ての時間から測定の為のオーバーヘッドを差し引いた時間の最小値。最小総実働時間＝(最小自実働時間＋最小子実働時間)。</TD></TR>
<TR class="check"><TD>最小自稼働時間</TD><TD>総実働時間が最小となった時のそのスコープ自身の実行に要した全ての時間(内包するスコープの時間は除く)。最小自稼働時間＝(最小自バグ時間＋最小自実働時間)。</TD></TR>
<TR><TD>最小自バグ時間</TD><TD>総実働時間が最小となった時のそのスコープ自身の測定の為に要した全ての時間(内包するスコープの時間は除く)。</TD></TR>
<TR class="check"><TD>最小自実働時間</TD><TD>総実働時間が最小となった時のその内包するスコープの実行に要した全ての時間。最小子稼働時間＝(最小子バグ時間＋最小子実働時間)。</TD></TR>
<TR><TD>最小子稼働時間</TD><TD>総実働時間が最小となった時のその内包するスコープの実行に要した全ての時間。最小子稼働時間＝(最小子バグ時間＋最小子実働時間)。</TD></TR>
<TR class="check"><TD>最小子バグ時間</TD><TD>総実働時間が最小となった時のその内包するスコープの測定の為に要した全ての時間。</TD></TR>
<TR><TD>最小子実働時間</TD><TD>総実働時間が最小となった時のその内包するスコープの実行に要した全ての時間から測定の為のオーバーヘッドを差し引いた時間。</TD></TR>
<TR class="check"><TD>最大スタンプ</TD><TD>総実働時間が最大となった時のそのスコープのロガー上でのスタンプ。</TD></TR>
<TR><TD>最大総稼働時間</TD><TD>総実働時間が最大となった時のそのスコープ自身とその内包するスコープの実行に要した全ての時間。最大総稼働時間＝(最大総バグ時間＋最大総実働時間)＝(最大自稼働時間＋最大子稼働時間)</TD></TR>
<TR class="check"><TD>最大総バグ時間</TD><TD>総実働時間が最大となった時のそのスコープ自身とその内包するスコープの測定の為に要した全てのオーバーヘッド。最大総バグ時間＝(最大自バグ時間＋最大子バグ時間)。</TD></TR>
<TR><TD>最大総実働時間</TD><TD>そのスコープ自身とその内包するスコープの実行に要した全ての時間から測定の為のオーバーヘッドを差し引いた時間の最大値。最大総実働時間＝(最大自実働時間＋最大子実働時間)。</TD></TR>
<TR class="check"><TD>最大自稼働時間</TD><TD>総実働時間が最大となった時のそのスコープ自身の実行に要した全ての時間(内包するスコープの時間は除く)。最大自稼働時間＝(最大自バグ時間＋最大自実働時間)。</TD></TR>
<TR><TD>最大自バグ時間</TD><TD>総実働時間が最大となった時のそのスコープ自身の測定の為に要した全ての時間(内包するスコープの時間は除く)。</TD></TR>
<TR class="check"><TD>最大自実働時間</TD><TD>総実働時間が最大となった時のその内包するスコープの実行に要した全ての時間。最大子稼働時間＝(最大子バグ時間＋最大子実働時間)。</TD></TR>
<TR><TD>最大子稼働時間</TD><TD>総実働時間が最大となった時のその内包するスコープの実行に要した全ての時間。最大子稼働時間＝(最大子バグ時間＋最大子実働時間)。</TD></TR>
<TR class="check"><TD>最大子バグ時間</TD><TD>総実働時間が最大となった時のその内包するスコープの測定の為に要した全ての時間。</TD></TR>
<TR><TD>最大子実働時間</TD><TD>総実働時間が最大となった時のその内包するスコープの実行に要した全ての時間から測定の為のオーバーヘッドを差し引いた時間。</TD></TR>
</TABLE>
<DIV class="comment">
    <IMG class="accessary" alt="Wraith the Trickster" src="/image/icon/wrth32.png">
    <P>
        「総＝自＋子」及び「稼働＝バグ＋実働」なんだと理解して頂ければ後はそれの応用です。
    </P>
</DIV>

## ダウンロード

バグベアード本体

- <A class="bar" href="/cxx/ex/bugbeard/bug.h">バグベアードモジュールヘッダファイル ( bug.h )</A>

サンプルコード

- <A class="bar" href="/cxx/ex/bugbeard/simple.cpp">"Hello, Bugbeard!" ( simple.cpp )</A>
- <A class="bar" href="/cxx/ex/bugbeard/win.cpp">Windows用情報収集サンプル ( win.cpp )</A>
- <A class="bar" href="/cxx/ex/bugbeard/tsv.cpp">.tsv形式ログ出力＆マルチスレッドサンプル ( tsv.cpp )</A>
- <A class="bar" href="/cxx/ex/bugbeard/bulklog.cpp">バルクログ出力サンプル ( bulklog.cpp )</A>
- <A class="bar" href="/cxx/ex/bugbeard/profile.cpp">プロファイル＆カバレッジ測定サンプル ( profile.cpp )</A>

アイコン

- <A class="bar" href="/cxx/ex/bugbeard/bugbeard.ico">バグベアードアイコンファイル ( bugbeard.ico )</A>
- <A class="bar" href="/cxx/ex/bugbeard/mini-bugbeard.ico">バグベアードオーバーレイ用アイコンファイル ( mini-bugbeard.ico )</A>

全ファイルパック

- <A class="bar" href="/cxx/ex/bugbeard/bug.zip">バグベアード全ファイルZIPパック ( bug.zip )</A>
    
## バグベアード入門

2009-12-12 に行われた<A href="http://atnd.org/events/1839">Boost.勉強会</A>で発表したバグベアード入門の ustream へのリンクと発表資料です。

- <A class="bar" href="http://www.ustream.tv/recorded/2980510">ustream の録画</A>

- <A class="bar" href="/cxx/ex/bugbeard/bugbeard.primer.pptx">発表資料 ( .pptx版 )</A>
- <A class="bar" href="/cxx/ex/bugbeard/bugbeard.primer.pdf">発表資料 ( .pdf版 )</A>
    
## links

- [DebugView ( Windows Sysinternals )](https://docs.microsoft.com/ja-jp/sysinternals/downloads/debugview)
