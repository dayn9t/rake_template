
int fun2_bench(int argc, const char *argv[]);

int main(int argc, const char *argv[])
{
	// 手动调用全部性能测试函数, 这里没提供如同单元测试那样的工具
	fun2_bench(argc, argv);
	return 0;
}