(define (make-tree entry left right)
  (list entry left right))

(define (entry tree) (car tree))
(define (left-branch tree) (cadr tree))
(define (right-branch tree) (caddr tree))

(define (key record)
  (car record))

(define (make-record k v)
  (list k v))

; our lookup procedure using a tree to store the records
(define (lookup given-key set-of-records)
  (cond ((null? set-of-records) #f)
        ((= given-key (key (entry set-of-records)))
         (entry set-of-records))
        ((< given-key (key (entry set-of-records)))
         (lookup given-key (left-branch set-of-records)))
        (else
          (lookup given-key (right-branch set-of-records)))))

(define db
  (make-tree
    (make-record 4 "Jonathan")
    (make-tree (make-record 2 "Samuel")
               (make-tree (make-record 1 "Alice") '() '())
               (make-tree (make-record 3 "Tom") '() '()))
    (make-tree (make-record 5 "Billy") '() '())))

(display (lookup 2 db)) (newline) ; (2 "Samuel")
(display (lookup 8 db)) (newline) ; #f
(display (lookup 0 db)) (newline) ; #f
