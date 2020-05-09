package myPkgs

import (
	"database/sql"
	"fmt"
	_ "github.com/go-sql-driver/mysql"
)

func checkErr(err error) {
	if err != nil {
		panic(err)
	}
}

type DbWorker struct {
	Dsn      string
	Db       *sql.DB
	UserInfo userTB
}
type userTB struct {
	Id   	sql.NullInt64
	ImgDat 	sql.RawBytes
}
//type userTB struct {
//	Id   int
//	Name sql.NullString
//	Age  sql.NullInt64
//}


func TestMysql() {
	var err error
	dbw := DbWorker{
		Dsn: "platformuser:123456@tcp(192.168.3.179:3306)/test?charset=utf8",
	}
	dbw.Db, err = sql.Open("mysql",dbw.Dsn)
	checkErr(err)

	defer dbw.Db.Close()

	dbw.insertData()
	dbw.queryData()


}


func (dbw *DbWorker) insertData() {
	stmt, _ := dbw.Db.Prepare(`INSERT INTO aaa ( imgDat) VALUES ( ?)`)
	defer stmt.Close()



	imgdat := []byte("aaaaaaaaaa")

	ret, err := stmt.Exec( imgdat)
	if err != nil {
		fmt.Printf("insert data error: %v\n", err)
		return
	}
	if LastInsertId, err := ret.LastInsertId(); nil == err {
		fmt.Println("LastInsertId:", LastInsertId)
	}
	if RowsAffected, err := ret.RowsAffected(); nil == err {
		fmt.Println("RowsAffected:", RowsAffected)
	}

	//stmt, _ := dbw.Db.Prepare(`INSERT INTO user (name, age) VALUES (?, ?)`)
	//defer stmt.Close()
	//
	//ret, err := stmt.Exec("xys", 23)
	//if err != nil {
	//	fmt.Printf("insert data error: %v\n", err)
	//	return
	//}
	//if LastInsertId, err := ret.LastInsertId(); nil == err {
	//	fmt.Println("LastInsertId:", LastInsertId)
	//}
	//if RowsAffected, err := ret.RowsAffected(); nil == err {
	//	fmt.Println("RowsAffected:", RowsAffected)
	//}
}

func (dbw *DbWorker) QueryDataPre() {
	dbw.UserInfo = userTB{}
}

func (dbw *DbWorker) queryData() {
	stmt, _ := dbw.Db.Prepare(`SELECT * From aaa where id >= ? AND id < ?`)
	//stmt, _ := dbw.Db.Prepare(`SELECT * From user where age >= ? AND age < ?`)

	defer stmt.Close()

	dbw.QueryDataPre()

	rows, err := stmt.Query(1, 2)
	defer rows.Close()
	if err != nil {
		fmt.Printf("insert data error: %v\n", err)
		return
	}
	for rows.Next() {
		rows.Scan(&dbw.UserInfo.Id, &dbw.UserInfo.ImgDat)
		if err != nil {
			fmt.Printf(err.Error())
			continue
		}
		fmt.Println("get data, id: ", dbw.UserInfo.Id, " imgDat: " , dbw.UserInfo.ImgDat)


		//rows.Scan(&dbw.UserInfo.Id, &dbw.UserInfo.Name, &dbw.UserInfo.Age)
		//if err != nil {
		//	fmt.Printf(err.Error())
		//	continue
		//}
		//if !dbw.UserInfo.Name.Valid {
		//	dbw.UserInfo.Name.String = ""
		//}
		//if !dbw.UserInfo.Age.Valid {
		//	dbw.UserInfo.Age.Int64 = 0
		//}
		//fmt.Println("get data, id: ", dbw.UserInfo.Id, " name: ", dbw.UserInfo.Name.String, " age: ", int(dbw.UserInfo.Age.Int64))
	}

	err = rows.Err()
	if err != nil {
		fmt.Printf(err.Error())
	}
}


