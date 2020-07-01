package main

import (
	"encoding/json"
	"net/http"
	"time"
)

const apiUrl = "https://api.github.com"

type Issue struct {
	ID        int64     `json:"id"`
	Number    int64     `json:"number"`
	Title     string    `json:"title"`
	CreatedAt time.Time `json:"created_at"`
	Body      string    `json:"body"`
	User      *User
}

type User struct {
	ID    int64  `json:"id"`
	Login string `json:"login"`
}

func getIssue(user_repo string, number int64) (*Issue, error) {
	url := apiUrl + "/repos/" + user_repo + "/issues/" + string(number)
	resp, err := http.Get(url)
	if err != nil {
		return nil, err
	}
	defer resp.Body.Close()
	var issue = Issue{}
	err = json.NewDecoder(resp.Body).Decode(&issue)
	if err != nil {
		return nil, err
	}
	return &issue, nil
}
