package memo

// Func is the type of the function to memoize.
type Func func(key string, done <-chan struct{}) (interface{}, error)

// A result is the result of calling a Func.
type result struct {
	value interface{}
	err   error
}

type entry struct {
	res   result
	ready chan struct{} // closed when res is ready
}

// A request is a message requesting that the Func be applied to key.
type request struct {
	key      string
	response chan<- result   // the client wants a single result
	done     <-chan struct{} // send the cancellation
}

type Memo struct {
	requests      chan request
	cancellations chan request
}

// New returns a memoization of f. Clients must subsequently call Close.
func New(f Func) *Memo {
	memo := &Memo{
		requests:      make(chan request),
		cancellations: make(chan request),
	}
	go memo.server(f)
	return memo
}

func (memo *Memo) Get(key string, done <-chan struct{}) (interface{}, error) {
	response := make(chan result)
	req := request{key, response, done}
	memo.requests <- req
	res := <-response
	select {
	case <-done: // request was cancelled
		memo.cancellations <- req
	default:
		// everything good
	}
	return res.value, res.err
}

func (memo *Memo) Close() { close(memo.requests) }

func (memo *Memo) server(f Func) {
	cache := make(map[string]*entry)
main:
	for {
	cancels:
		for {
			select {
			case req := <-memo.cancellations:
				// request was cancelled, remove from cache
				delete(cache, req.key)
			default:
				break cancels
			}
		}

		select {
		case req := <-memo.cancellations:
			// request was cancelled, remove from cache
			delete(cache, req.key)
			continue main
		case req := <-memo.requests:
			e := cache[req.key]
			if e == nil {
				// This is the first request for this key.
				e = &entry{ready: make(chan struct{})}
				cache[req.key] = e
				go e.call(f, req.key, req.done) // call f(key)
			}
			go e.deliver(req.response)
		}
	}
}

func (e *entry) call(f Func, key string, done <-chan struct{}) {
	// Evaluate the function.
	e.res.value, e.res.err = f(key, done)
	// Broadcast the ready condition.
	close(e.ready)
}

func (e *entry) deliver(response chan<- result) {
	// Wait for the ready condition.
	<-e.ready
	// Send the result to the client.
	response <- e.res
}
