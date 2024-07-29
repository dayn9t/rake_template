
#include <hen/reader/downloader.h>
#include <fmt/format.h>

using namespace std;

int main(int argc, const char* argv[])
{
	if (argc != 3)
	{
		fmt::println("Usage:\n\then-download <URL> <DST_FILE>\n");
		return 2;
	}

	const char* src_url = argv[1];
	const char* dst_file = argv[2];
	auto downloader = hen_downloader_create(src_url, dst_file);

	auto size = hen_downloader_transfer(downloader);

	fmt::println("Download size: {}", size);

	hen_downloader_destroy(downloader);

	fmt::println("Done");

	return 0;
}
