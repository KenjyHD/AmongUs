#include "utils.h"

void *(*Abilities[4]) (void *x) =
{
RotateMatrix, DecodeString, InvertArray, KillPlayer};

char *
fromEnumtoString (PlayerRoles playerRole)
{
  char *str = calloc (MAX_LEN_STR_ATR, sizeof (char));
  switch (playerRole)
    {
    case Rotator:
      str = strcpy (str, "Rotator");
      break;
    case Decoder:
      str = strcpy (str, "Decoder");
      break;
    case Invertor:
      str = strcpy (str, "Invertor");
      break;
    case Impostor:
      str = strcpy (str, "Impostor");
      break;
    }

  return str;
}

// Task 1
void *
RotateMatrix (void *input)
{

  int n = *(int *) input;
  char *s = malloc (sizeof (char) * MAX_LEN_STR_OUT);
  char *s1 = malloc (sizeof (char) * 20);

  for (int i = 1; i <= n; i++)
    {
      for (int j = n; j >= 1; j--)
	{
	  if ((j == n) && (i == 1))
	    {
	      snprintf (s, 4, "%d", j);
	      snprintf (s1, 4, "%d ", i);
	      strcat (s, s1);
	    }
	  else
	    {
	      snprintf (s1, 4, "%d", j);
	      strcat (s, s1);
	      snprintf (s1, 4, "%d", i);
	      strcat (s, s1);
	      if (j > 1)
		{
		  snprintf (s1, 4, " ");
		  strcat (s, s1);
		}
	    }
	}
      if (i < n)
	{
	  snprintf (s1, 4, "\n");
	  strcat (s, s1);
	}
    }
  free (s1);
  return s;
}

// Task 2
void *
DecodeString (void *input)
{
  char *s = malloc (sizeof (char) * MAX_LEN_STR_ATR);
  char *res = malloc (sizeof (char) * MAX_LEN_STR_OUT);
  char *aux = malloc (sizeof (char) * 20);
  int last_pos = 0, n, sum = 0, i = 0;

  s = (char *) input;
  for (i = 0; s[i] != '\0'; i++)
    if (s[i] == '_')
      {
	memset (aux, 0, 20);
	strncpy (aux, s + last_pos, i - last_pos);
	sscanf (aux, "%d", &n);
	sum = sum + n;
	last_pos = i + 1;
      }
  memset (aux, 0, 20);
  strncpy (aux, s + last_pos, i - last_pos);
  sscanf (aux, "%d", &n);
  sum = sum + n;
  sprintf (res, "%d", sum);
  free (aux);
  return res;
}

//Task 3
void *
InvertArray (void *input)
{
  int *a = malloc (sizeof (char) * MAX_LEN_STR_ATR);
  char *res = malloc (sizeof (char) * MAX_LEN_STR_OUT);
  char *aux = malloc (sizeof (char) * MAX_LEN_STR_ATR);
  int i = 0;

  a = (int *) input;

  if (a[0] % 2 == 1)
    for (i = a[0]; i > 0; i--)
      {
	sprintf (aux, "%d ", a[i]);
	strcat (res, aux);
      }
  else
    for (i = 1; i < a[0]; i++)
      if (i % 2 == 1)
	{
	  sprintf (aux, "%d ", a[i + 1]);
	  strcat (res, aux);
	  sprintf (aux, "%d ", a[i]);
	  strcat (res, aux);
	  i++;
	}
  free (aux);
  return res;
}

//Task 4
Player *
allocPlayer ()
{
  Player *a;
  a = calloc (1, sizeof (Player));
  a->name = malloc (sizeof (char) * MAX_LEN_STR_ATR);
  a->color = malloc (sizeof (char) * MAX_LEN_STR_ATR);
  a->hat = malloc (sizeof (char) * MAX_LEN_STR_ATR);
  a->alive = 1;
  return a;
}

//Task 4
Game *
allocGame ()
{
  Game *a;
  a = malloc (sizeof (Game));
  a->name = malloc (sizeof (char) * MAX_LEN_STR_ATR);
  return a;
}

//Task 5
Player *
ReadPlayer (FILE * inputFile)
{
  Player *player;
  player = malloc (sizeof (Player));
  player->name = malloc (sizeof (char) * MAX_LEN_STR_ATR);
  player->color = malloc (sizeof (char) * MAX_LEN_STR_ATR);
  player->hat = malloc (sizeof (char) * MAX_LEN_STR_ATR);
  fscanf (inputFile, "%s\n", player->name);
  fscanf (inputFile, "%s\n", player->color);
  fscanf (inputFile, "%s\n", player->hat);
  fscanf (inputFile, "%d", &(player->numberOfLocations));
  player->alive = 1;

  char *location = malloc (sizeof (char) * 60);
  char *slocation_x = malloc (30 * sizeof (char));
  char *slocation_y = malloc (30 * sizeof (char));
  int x, y;

  memset (location, 0, 20);
  player->locations = malloc (sizeof (Location) * player->numberOfLocations);
  for (int i = 0; i < player->numberOfLocations; i++)
    {
      fscanf (inputFile, "%s", location);

      for (int j = 0; location[j] != '\0'; j++)
	{
	  if (location[j] == ',')
	    x = j;
	  if (location[j] == ')')
	    y = j;
	}
      memset (slocation_x, 0, 30);
      memset (slocation_y, 0, 30);
      strncpy (slocation_x, location + 1, x - 1);
      strncpy (slocation_y, location + x + 1, y - x - 1);

      player->locations[i].x = atoi (slocation_x);
      player->locations[i].y = atoi (slocation_y);

    }
  free (location);
  free (slocation_x);
  free (slocation_y);
  char *role = malloc (10 * sizeof (char));
  memset (role, 0, 10);
  fscanf (inputFile, "%s", role);
  if (strcmp (role, "Rotator") == 0)
    player->playerRole = 0;
  if (strcmp (role, "Decoder") == 0)
    player->playerRole = 1;
  if (strcmp (role, "Invertor") == 0)
    player->playerRole = 2;
  if (strcmp (role, "Impostor") == 0)
    player->playerRole = 3;
  player->ability = Abilities[player->playerRole];
  return player;
}

// Task 5
Game *
ReadGame (FILE * inputFile)
{
  Game *joc;

  joc = malloc (sizeof (Game));
  joc->name = malloc (sizeof (char) * MAX_LEN_STR_ATR);

  fscanf (inputFile, "%s\n", joc->name);
  fscanf (inputFile, "%d", &(joc->killRange));
  fscanf (inputFile, "%d", &(joc->numberOfCrewmates));


  (joc->crewmates) = malloc (sizeof (Player) * joc->numberOfCrewmates);

  for (int i = 0; i < joc->numberOfCrewmates; i++)
    {
      *(joc->crewmates + i) = malloc (sizeof (Player));

      joc->crewmates[i] = ReadPlayer (inputFile);
    }
  joc->impostor = ReadPlayer (inputFile);
  return joc;
}

// Task 6
void
WritePlayer (Player * player, FILE * outputFile)
{
  char *role;
  role = fromEnumtoString (player->playerRole);
  if (player->playerRole == 3)
    {
      fprintf (outputFile, "\n");
      fprintf (outputFile, "\tImpostor:\n");
    }
  fprintf
    (outputFile,
     "Player %s with color %s, hat %s and role %s has entered the game.\n",
     player->name, player->color, player->hat, role);
  fprintf (outputFile, "Player's locations: ");
  for (int i = 0; i < player->numberOfLocations; i++)
    {
      fprintf (outputFile, "(%d,%d) ",
	       player->locations[i].x, player->locations[i].y);
    }
  fprintf (outputFile, "\n");

  free (role);
  return;
}

// Task 6
void
WriteGame (Game * game, FILE * outputFile)
{
  fprintf (outputFile, "Game %s has just started!\n", game->name);
  fprintf (outputFile, "\tGame options:\n");
  fprintf (outputFile, "Kill Range: %d\n", game->killRange);
  fprintf (outputFile, "Number of crewmates: %d\n\n",
	   game->numberOfCrewmates);
  fprintf (outputFile, "\tCrewmates:\n");
  for (int i = 0; i < game->numberOfCrewmates; i++)
    {
      WritePlayer (game->crewmates[i], outputFile);
    }

  WritePlayer (game->impostor, outputFile);
  return;
}

static int cycle;
//Task 7
void *
KillPlayer (void *input)
{
  int distance = 1000, min_distance = 500, index = -1, j = -1, k = -1;
  Game *game = input;

  for (int i = 0; i < game->numberOfCrewmates; i++)
    {
      if (game->crewmates[i]->alive == 1)
	{
	  j = cycle % game->impostor->numberOfLocations;
	  k = cycle % game->crewmates[i]->numberOfLocations;
	  distance = (abs (game->crewmates[i]->locations[k].x -
			   game->impostor->locations[j].x)) +
	    (abs (game->crewmates[i]->locations[k].y -
		  game->impostor->locations[j].y));

	  if ((min_distance >= distance))
	    {
	      index = i;
	      min_distance = distance;
	    }
	}
    }

  char *res = malloc (80 * sizeof (char));
  memset (res, 0, 80 * sizeof (char));
  if ((min_distance <= game->killRange) &&
      (game->crewmates[index]->alive == 1))
    {
      sprintf (res,
	       "Impostor %s has just killed crewmate %s from distance %d.",
	       game->impostor->name, game->crewmates[index]->name,
	       min_distance);
      game->crewmates[index]->alive = 0;
    }
  else
    sprintf (res, "Impostor %s couldn't kill anybody.", game->impostor->name);
  return res;
}

// Task 8
void
CalcuateNextCycleOfGame (Game * game, FILE * outputFile, void **inputMatrix)
{

  char *n = malloc (sizeof (char) * MAX_LEN_STR_ATR);
  int i = 0, j = -1, k = -1;

  cycle++;
  for (i = 0; i < game->numberOfCrewmates; i++)
    {

      j = cycle % game->impostor->numberOfLocations;
      k = cycle % game->crewmates[i]->numberOfLocations;
      if (game->crewmates[i]->alive == 1)
	{
	  fprintf (outputFile, "Crewmate %s went to location (%d,%d).\n",
		   game->crewmates[i]->name,
		   game->crewmates[i]->locations[k].x,
		   game->crewmates[i]->locations[k].y);
	  n = Abilities[game->crewmates[i]->playerRole] (inputMatrix[i]);
	  fprintf (outputFile,
		   "Crewmate %s's output:\n%s\n", game->crewmates[i]->name,
		   n);
	}
      else
	fprintf (outputFile,
		 "Crewmate %s is dead.\n", game->crewmates[i]->name);
    }

  n = Abilities[game->impostor->playerRole] (inputMatrix[i]);
  fprintf (outputFile, "Impostor %s went to location (%d,%d).\n",
	   game->impostor->name, game->impostor->locations[j].x,
	   game->impostor->locations[j].y);
  fprintf (outputFile, "Impostor %s's output:\n%s\n", game->impostor->name,
	   n);
  free (n);


  return;
}

// Task 9
void
FreePlayer (Player * player)
{
  // TODO
  return;
}

// Task 9
void
FreeGame (Game * game)
{
  // TODO
  return;
}

