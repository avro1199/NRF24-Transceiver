void motor(int lsp, int rsp)
{
  if(lsp >= 0)
  {
    digitalWrite(lmf, 1);
    digitalWrite(lmb, 0);
  }
  else if(lsp < 0)
  {
    lsp = -lsp;
    digitalWrite(lmf, 0);
    digitalWrite(lmb, 1);
  }

  if(rsp >= 0)
  {
    digitalWrite(rmf, 1);
    digitalWrite(rmb, 0);
  }
  else if(rsp < 0)
  {
    rsp = -rsp;
    digitalWrite(rmf, 0);
    digitalWrite(rmb, 1);
  }

  analogWrite(lms, lsp);
  analogWrite(rms, rsp);
}