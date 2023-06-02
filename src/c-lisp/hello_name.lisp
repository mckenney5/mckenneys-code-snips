;;;; Common Lisp (clisp)
;;; Takes input from the user and says hello
;;; to run type: clisp common-lisp.lisp

;; makes the text capitalized instead of lower case
(setq *print-case* :capitalize)

;; prompt
(format t "Enter your name: ")

;; get user input
(defvar *name* (read))

;; say hello
(format t "Hello ~a! ~%" *name*)

