echo "/opt/ejudge/bin/ejudge-fuse --user $EJUDGE_USER --password $EJUDGE_PASSWORD --url https://unicorn.ejudge.ru/cgi-bin/ ~/contest -o use_ino" | ssh $EJUDGE_USER@$EJUDGE_SERVER "bash -s"
