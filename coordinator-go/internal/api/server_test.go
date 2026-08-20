package api
import("net/http/httptest";"testing")
func TestHealth(t *testing.T){r:=httptest.NewRequest("GET","/health",nil);w:=httptest.NewRecorder();Handler().ServeHTTP(w,r);if w.Code!=200{t.Fatal(w.Code)}}
