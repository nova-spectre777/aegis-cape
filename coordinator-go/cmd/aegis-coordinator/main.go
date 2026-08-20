package main
import("log";"net/http";"github.com/nova-spectre777/aegis/coordinator-go/internal/api")
func main(){log.Println("AEGIS coordinator on :8787");log.Fatal(http.ListenAndServe("127.0.0.1:8787",api.Handler()))}
