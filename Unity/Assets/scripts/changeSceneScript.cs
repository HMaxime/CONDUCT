using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

/*
Ce script permet de changer de scène avec un délai de 3 secondes.
*/
public class changeSceneScript : MonoBehaviour {
    public void GoToScene (string nameScene) {
        StartCoroutine(waitNSecondsAndgo (3,nameScene));
    }

    IEnumerator waitNSecondsAndgo (int nbSeconds, string nameScene) {
        yield return new WaitForSeconds (3);
        SceneManager.LoadScene (nameScene);
    }
}