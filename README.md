# Generat-Hashtable-from-BIN
Generat Hashtable from League of Legends BIN File<br>

从bin文件生成哈希表<br>

跟老外不是同一种思路，老外是通过分析bin结构得到哈希表，我的思路是分析二进制<br>
分析bin结构会受到bin版本限制，如果bin改版，他的分析哈希功能就要重新维护<br>
我的方法不会受到bin版本限制<br>

如何从wad历遍哈希表？需要读入wad逐个条目分析，如果是bin就把二进制过滤一遍，看看里面有没有需要的内容<br>

