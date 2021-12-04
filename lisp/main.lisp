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
