(defun read-file-as-lines (filename)
  "Read file into list of lines."
  (with-open-file (in filename)
    (loop for line = (read-line in nil nil)
          while line
          collect line)))

(defvar *ex01-example* '(199 200 208 210 200 207 240 269 260 263))

(defun ex01-work (xs car-fn)
  (apply #'+
         (mapcon #'(lambda (x)
                     (cond
                       ((not (funcall car-fn x)) nil)
                       ((< (car x) (funcall car-fn x)) (list 1))
                       (nil)))
                 xs)))

(defun ex01a-work (xs)
  (ex01-work xs #'cadr))

(defun ex01b-work (xs)
  (ex01-work xs #'cadddr))

(defun ex01 ()
  (let ((ex01-input (mapcar #'read-from-string (read-file-as-lines "../input/01"))))
    (list (ex01a-work ex01-input) (ex01b-work ex01-input))))


(defun ex02-parse (x)
  (read-from-string (concatenate 'string "(:" x ")")))

(defun ex02a-diff (dh dirx)
  (let ((d (car dh))
        (h (cadr dh))
        (dir (car dirx))
        (x (cadr dirx)))
  (cond
    ((equal dir :forward) (list d (+ h x)))
    ((equal dir :up) (list (- d x) h))
    ((equal dir :down) (list (+ d x) h)))))

(defun ex02a-work (xs)
  (loop for fold = '(0 0) then (ex02a-diff fold element)
        for element in xs
        finally (return (apply #'* fold))))

(defun ex02b-diff (dha dirx)
  (let ((d (car dha))
        (h (cadr dha))
        (a (caddr dha))
        (dir (car dirx))
        (x (cadr dirx)))
  (cond
    ((equal dir :forward) (list (+ d (* x a)) (+ h x) a))
    ((equal dir :up) (list d h (- a x)))
    ((equal dir :down) (list d h (+ a x))))))

(defun ex02b-work (xs)
  (loop for fold = '(0 0 0) then (ex02b-diff fold element)
        for element in xs
        finally (return (* (car fold) (cadr fold)))))

(defun ex02 ()
  (let ((ex02-input (mapcar #'ex02-parse (read-file-as-lines "../input/02"))))
    (list (ex02a-work ex02-input) (ex02b-work ex02-input))))
