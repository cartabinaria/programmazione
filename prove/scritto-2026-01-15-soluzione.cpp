// ------------- ESERCIZIO 1 -------------

bool is_prime(int n)
{
  if (n <= 1) return false;

  for (int i = 2; i*i <= n; ++i)
    if (n % i == 0) return false;

  return true;
}

bool only_primes(int A[], int length)
{
  for (int i = 0; i < length; ++i)
    if (!is_prime(A[i])) return false;

  return true;
}


// ------------- ESERCIZIO 2 -------------

struct tree
{
  int val;
  tree *ltree;
  tree *ctree;
  tree *rtree;
};
typedef tree *ptree;

// Pari -> si spostano a sinistra
// Dispari -> si spostano a destra
ptree ammuina(ptree T)
{
  if (!T) return nullptr;

  if (T->val % 2 == 0)
  {
    tree* rt{ T->rtree };
    tree* ct{ T->ctree };
    T->rtree = T->ltree;
    T->ctree = rt;
    T->ltree = ct;
  }
  else
  {
    tree* lt{ T->ltree };
    tree* ct{ T->ctree };
    T->ltree = T->rtree;
    T->ctree = lt;
    T->rtree = ct;
  }

  T->ltree = ammuina(T->ltree);
  T->ctree = ammuina(T->ctree);
  T->rtree = ammuina(T->rtree);

  return T;
}

ptree upgrade10(ptree T)
{
  if (!T) return nullptr;

  if (!T->ltree && !T->ctree && !T->rtree)
  {
    if (T->val < 10)
    {
      delete T;
      return nullptr;
    }
    T->val += 10;
    return T;
  }

  T->ltree = upgrade10(T->ltree);
  T->ctree = upgrade10(T->ctree);
  T->rtree = upgrade10(T->rtree);

  return T;
}

// ------------- ESERCIZIO 3 -------------

class Abitazione
{
public:
  Abitazione(int n, double m)
    : m_numStanze{ n }
    , m_metratura{ m }
  { }

  double costo_abitazione(double p)
  {
    return m_metratura * p;
  }

protected:
  int m_numStanze{};
  double m_metratura{};
};

class Villetta: public Abitazione
{
public:
  Villetta(int n, double m)
    : Abitazione{ n, m }
  { }

  double costo_abitazione(double p)
  {
    double prezzo{ Abitazione::costo_abitazione(p) };
    return prezzo + (prezzo * 0.2);
  }
};

class Appartamento: public Abitazione
{
public:
  Appartamento(int n, double m, int p)
    : Abitazione{ n, m }
    , m_piano{ p }
  { }

  double costo_abitazione(double p)
  {
    double prezzo{ Abitazione::costo_abitazione(p) };
    
    if (m_piano > 5)
      return prezzo + (prezzo * 0.1);
    else
      return prezzo;
  }

  int num_piano()
  {
    return m_piano;
  }

protected:
  int m_piano{};
};