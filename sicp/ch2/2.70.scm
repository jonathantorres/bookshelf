(define (make-leaf symbol weight)
  (list 'leaf symbol weight))

(define (leaf? object)
  (eq? (car object) 'leaf))

(define (symbol-leaf x) (cadr x))
(define (weight-leaf x) (caddr x))

(define (left-branch tree) (car tree))
(define (right-branch tree) (cadr tree))

(define (symbols tree)
  (if (leaf? tree)
    (list (symbol-leaf tree))
    (caddr tree)))

(define (weight tree)
  (if (leaf? tree)
    (weight-leaf tree)
    (cadddr tree)))

(define (adjoin-set x set)
  (cond ((null? set) (list x))
        ((< (weight x) (weight (car set))) (cons x set))
        (else
          (cons (car set)
                (adjoin-set x (cdr set))))))

(define (element-of-set? x set)
  (cond ((null? set) #f)
        ((eq? x (car set)) #t)
        (else (element-of-set? x (cdr set)))))

(define (encode message tree)
  (if (null? message)
    '()
    (append (encode-symbol (car message) tree)
            (encode (cdr message) tree))))

(define (encode-symbol symbol tree)
  (if (leaf? tree)
    '()
    (let ((left (left-branch tree))
          (right (right-branch tree)))
      (cond ((element-of-set? symbol (symbols left))
             (cons 0 (encode-symbol symbol left)))
            ((element-of-set? symbol (symbols right))
             (cons 1 (encode-symbol symbol right)))
            (else
              (error "symbol is not in tree -- ENCODE SYMBOL" symbol))))))

(define (make-code-tree left right)
  (list left
        right
        (append (symbols left) (symbols right))
        (+ (weight left) (weight right))))

(define (make-leaf-set pairs)
  (if (null? pairs)
    '()
    (let ((pair (car pairs)))
      (adjoin-set (make-leaf (car pair)
                             (cadr pair))
                  (make-leaf-set (cdr pairs))))))

(define (successive-merge set)
  (if (= (length set) 1)
    (car set)
    (let ((left (car set))
          (right (cadr set)))
      (let ((code-tree (make-code-tree left right)))
        (successive-merge
          (adjoin-set code-tree (cddr set)))))))

(define (generate-huffman-tree pairs)
  (successive-merge (make-leaf-set pairs)))

(define lyrics '((A 2) (BOOM 1) (GET 2) (JOB 2) (NA 16) (SHA 3) (YIP 9) (WAH 1)))

(define tree (generate-huffman-tree lyrics))

(define message '(GET A JOB SHA NA NA NA NA NA NA NA NA
                  GET A JOB SHA NA NA NA NA NA NA NA NA
                  WAH YIP YIP YIP YIP YIP YIP YIP YIP YIP SHA BOOM))

; 84 bits are required to encode the message
; 108 bits would be required to encode the message if we used a fixed-length encoding

(display (encode message tree)) (newline)
(display (length (encode message tree))) (newline)
