using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class changeSceneScript : MonoBehaviour {
    public void GoToScene (string nameScene) {
        StartCoroutine(waitNSecondsAndgo (3,nameScene));
    }

    IEnumerator waitNSecondsAndgo (int nbSeconds, string nameScene) {
        yield return new WaitForSeconds (3);
        SceneManager.LoadScene (nameScene);
    }

}