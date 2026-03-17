package main

import (
	"bytes"
	"encoding/json"
	"errors"
	"net/http"
	"strconv"
	"time"
)

const apiUrl = "https://api.github.com"
const oauthToken = "API_TOKEN" // Replace with your oauth2 token

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

type CreateIssue struct {
	Title string `json:"title"`
	Body  string `json:"body"`
}

type CloseIssue struct {
	State string `json:"state"`
}

func getIssue(user_repo string, number int64) (*Issue, error) {
	url := apiUrl + "/repos/" + user_repo + "/issues/" + strconv.Itoa(int(number))
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

func sendRequest(url string, mode string, body interface{}) (*http.Response, error) {
	client := &http.Client{}
	bodyJson, err := json.Marshal(body)
	if err != nil {
		return nil, err
	}
	req, err := http.NewRequest(mode, url, bytes.NewBuffer(bodyJson))
	if err != nil {
		return nil, err
	}
	req.Header.Add("Authorization", "token "+oauthToken)
	return client.Do(req)
}

func updateExistingIssue(user_repo string, number int64, title string, content string) (bool, error) {
	url := apiUrl + "/repos/" + user_repo + "/issues/" + strconv.Itoa(int(number))
	body := CreateIssue{
		Title: title,
		Body:  content,
	}
	resp, err := sendRequest(url, "PATCH", &body)
	if err != nil {
		return false, err
	}
	defer resp.Body.Close()
	if resp.StatusCode != 200 {
		return false, errors.New("There was something wrong with your request " + resp.Status)
	}
	return true, nil
}

func closeExistingIssue(user_repo string, number int64) (bool, error) {
	url := apiUrl + "/repos/" + user_repo + "/issues/" + strconv.Itoa(int(number))
	body := CloseIssue{
		State: "closed",
	}
	resp, err := sendRequest(url, "PATCH", &body)
	if err != nil {
		return false, err
	}
	defer resp.Body.Close()
	if resp.StatusCode != 200 {
		return false, errors.New("There was something wrong with your request " + resp.Status)
	}
	return true, nil
}

func createNewIssue(user_repo string, title string, content string) (bool, error) {
	url := apiUrl + "/repos/" + user_repo + "/issues"
	body := CreateIssue{
		Title: title,
		Body:  content,
	}
	resp, err := sendRequest(url, "POST", &body)
	if err != nil {
		return false, err
	}
	defer resp.Body.Close()
	if resp.StatusCode != 201 {
		return false, errors.New("There was something wrong with your request " + resp.Status)
	}
	return true, nil
}
