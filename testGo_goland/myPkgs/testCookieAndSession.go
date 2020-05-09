package myPkgs

import (
	//"encoding/base64"
	//"fmt"
	//"html/template"
	//"math/rand"
	//"net/http"
	//"net/url"
	//"sync"
	//"time"
	"fmt"
	"net/http"
)


type myHd struct {
}

func (h *myHd) ServeHTTP(w http.ResponseWriter, r *http.Request){
	//w.Write([]byte("hello world!"))

	fmt.Println(r.Cookies())

	//expiration := time.Now()
	//expiration = expiration.AddDate(0, 0, 1)
	//cookie := http.Cookie{Name: "username", Value: "astaxie", Expires: expiration}
	//http.SetCookie(w, &cookie)

	fmt.Fprintf(w,"hello world!")
	fmt.Println(r.Cookies())
}

func TestCK() {

	http.Handle("/",new(myHd))
	http.ListenAndServe(":3000",nil)
}

////////////////////////////////////////////////////////////////////////
//
////定义一个全局的session管理器
//type Provider interface {
//	SessionInit(sid string) (Session, error)
//	SessionRead(sid string) (Session, error)
//	SessionDestroy(sid string) error
//	SessionGC(maxLifeTime int64)
//}
//
//type Session interface {
//	Set(key, value interface{}) error // set session value
//	Get(key interface{}) interface{}  // get session value
//	Delete(key interface{}) error     // delete session value
//	SessionID() string                // back current sessionID
//}
//
//type Manager struct {
//	cookieName  string     // private cookiename
//	lock        sync.Mutex // protects session
//	provider    Provider
//	maxLifeTime int64
//}
//
//func NewManager(provideName, cookieName string, maxLifeTime int64) (*Manager, error) {
//	provider, ok := provides[provideName]
//	if !ok {
//		return nil, fmt.Errorf("session: unknown provide %q (forgotten import?)", provideName)
//	}
//	return &Manager{provider: provider, cookieName: cookieName, maxLifeTime: maxLifeTime}, nil
//}
//
//
//var session Session
//
//var globalSessions *session.Manager
////然后在init函数中初始化
//func initCK() {
//	globalSessions, _ = NewManager("memory", "gosessionid", 3600)
//}
//
//var provides = make(map[string]Provider)
//
//func Register(name string, provider Provider) {
//	if provider == nil {
//		panic("session: Register provider is nil")
//	}
//	if _, dup := provides[name]; dup {
//		panic("session: Register called twice for provider " + name)
//	}
//	provides[name] = provider
//}
//
//func (manager *Manager) sessionId() string {
//	b := make([]byte, 32)
//	if _, err := rand.Read(b); err != nil {
//		return ""
//	}
//	return base64.URLEncoding.EncodeToString(b)
//}
//
//func (manager *Manager) SessionStart(w http.ResponseWriter, r *http.Request) (session Session) {
//	manager.lock.Lock()
//	defer manager.lock.Unlock()
//	cookie, err := r.Cookie(manager.cookieName)
//	if err != nil || cookie.Value == "" {
//		sid := manager.sessionId()
//		session, _ = manager.provider.SessionInit(sid)
//		cookie := http.Cookie{Name: manager.cookieName,
//							 	Value: url.QueryEscape(sid),
//							 	Path: "/",
//								HttpOnly: true,
//								MaxAge: int(manager.maxLifeTime)}
//		http.SetCookie(w, &cookie)
//	} else {
//		sid, _ := url.QueryUnescape(cookie.Value)
//		session, _ = manager.provider.SessionRead(sid)
//	}
//	return
//}
//
//func login(w http.ResponseWriter, r *http.Request) {
//	sess := globalSessions.SessionStart(w, r)
//	r.ParseForm()
//	if r.Method == "GET" {
//		t, _ := template.ParseFiles("./myPkg2/html/login.gtpl")
//		w.Header().Set("Content-Type", "text/html")
//		t.Execute(w, sess.Get("username"))
//	} else {
//		sess.Set("username", r.Form["username"])
//		http.Redirect(w, r, "/", 302)
//	}
//}
//
//func count(w http.ResponseWriter, r *http.Request) {
//	sess := globalSessions.SessionStart(w, r)
//	createtime := sess.Get("createtime")
//	if createtime == nil {
//		sess.Set("createtime", time.Now().Unix())
//	} else if (createtime.(int64) + 360) < (time.Now().Unix()) {
//		globalSessions.SessionDestroy(w, r)
//		sess = globalSessions.SessionStart(w, r)
//	}
//	ct := sess.Get("countnum")
//	if ct == nil {
//		sess.Set("countnum", 1)
//	} else {
//		sess.Set("countnum", (ct.(int) + 1))
//	}
//	t, _ := template.ParseFiles("count.gtpl")
//	w.Header().Set("Content-Type", "text/html")
//	t.Execute(w, sess.Get("countnum"))
//}
//
////Destroy sessionid
//func (manager *Manager) SessionDestroy(w http.ResponseWriter, r *http.Request){
//	cookie, err := r.Cookie(manager.cookieName)
//	if err != nil || cookie.Value == "" {
//		return
//	} else {
//		manager.lock.Lock()
//		defer manager.lock.Unlock()
//		manager.provider.SessionDestroy(cookie.Value)
//		expiration := time.Now()
//		cookie := http.Cookie{Name: manager.cookieName, Path: "/", HttpOnly: true, Expires: expiration, MaxAge: -1}
//		http.SetCookie(w, &cookie)
//	}
//}
//
//func (manager *Manager) GC() {
//	manager.lock.Lock()
//	defer manager.lock.Unlock()
//	manager.provider.SessionGC(manager.maxLifeTime)
//	time.AfterFunc(time.Duration(manager.maxLifeTime), func() { manager.GC() })
//}