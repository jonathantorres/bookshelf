; a: Each division's file is tagged with an id for the division and installed
;    on the company-wide table, each division implements it's own get-record function
(define (get-record name file)
  (let ((division (file-division file)))
    (let ((record ((get 'get-record division) (file-content file))))
      (if (= record #f)
        #f ; record not found
        (attach-tag division record)))))

; b: Each division must implement it's own "get-salary" function
;    and have it installed on the company-wide table
(define (get-salary record)
  (let ((division (record-division record)))
    ((get 'get-salary division) (record-content record))))

; c: The find-record procedure would search all the division's files
;    and call the get-record function until the employee is found
(define (find-record name files)
  (if (null? files)
    #f ; record not found
    (let ((record (get-record name (car files))))
      (if (= record #f)
        (find-record name (cdr files)) ; try to find the record on the next division file
        record)))) ; record found

; d: Assign a new unique id to identify the new division and implement the appropriate
;    get-record and get-salary for this division and install them on the company-wide table.
