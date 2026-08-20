.PHONY: check demo
check:
	./scripts/check_all.sh
demo:
	cmake -S engine-cpp -B engine-cpp/build && cmake --build engine-cpp/build && ./engine-cpp/build/aegis-cape
